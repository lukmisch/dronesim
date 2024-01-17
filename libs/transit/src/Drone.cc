#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

// Strategy Imports
#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

// State imports
#include "IdleState.h"
#include "TransitState.h"
#include "DeliverState.h"

#include "DataCollection.h"

#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  state = new IdleState(this);
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (state) delete state;
}

void Drone::changeState(IDroneState* newState) {
  if (state) delete state;
  this->state = newState;
}

bool Drone::pathComplete(bool hasPackage) {
  if (!hasPackage) {
    // true if toPackage doesn't exist,
    // returns toPackage->isCompleted() otherwise
    return (!toPackage) ? true : toPackage->isCompleted();
  } else {
    // true if toFinalDestination doesn't exist, returns
    // toFinalDestination->isCompleted() otherwise
    return (!toFinalDestination) ? true : toFinalDestination->isCompleted();
  }
}

void Drone::moveDrone(double dt, bool hasPackage) {
  if (!hasPackage) {
    toPackage->move(this, dt);
  } else {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }
  }
  distanceThisDelivery += dt * speed;
}

void Drone::pickUpPackage() {
  if (toPackage && toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;

      if (state) delete state;
      state = new DeliverState(this);
  }
}

void Drone::dropoffPackage() {
  if (toFinalDestination && toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;

      if (state) delete state;
      state = new IdleState(this);
  }
  timeThisDelivery = model->getTime() - timeThisDelivery;
  DataCollection::getInstance()->addDroneTrip(id,
                                              distanceThisDelivery,
                                              timeThisDelivery,
                                              totalFee);
  distanceThisDelivery = 0;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination =
          new JumpDecorator(
            new AstarStrategy(
              packagePosition,
              finalDestination,
              model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new DijkstraStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else {
        toFinalDestination = new BeelineStrategy(
          packagePosition,
          finalDestination);
      }

      if (state) delete state;
      state = new TransitState(this);

      timeThisDelivery = model->getTime();
    }
  }
}

void Drone::update(double dt) {
  state->updateDrone(dt);
}

void Drone::decrementFee(double dec, double dt) {
  if (feeThisDelivery > MIN_FEE) {
    feeThisDelivery -= dec * dt;
  }
}

void Drone::resetFee() {
  totalFee += feeThisDelivery;
  feeThisDelivery = MAX_FEE;
}
