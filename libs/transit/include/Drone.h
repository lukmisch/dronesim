#ifndef DRONE_H_
#define DRONE_H_

#include <vector>
#include "math/vector3.h"

#include "IEntity.h"
#include "IStrategy.h"
#include "IDroneState.h"

class Package;


// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Changes the drone's state
   * @param newState New state
   */
  void changeState(IDroneState* newState);

  /**
   * @brief returns the completion state of one of two drone paths
   * @param hasPackage flag to indicate the current path strat
   *  @return completion status of the current path
   *  true -> toPackage
   *  false -> toFinalDestination
   *  if either pointer is a nullptr it returns true
   */
  bool pathComplete(bool hasPackage);

  /**
   * @brief moves the drone along it's current objective.
   * @param hasPackage flag to indicate the current path strat
   *  @return completion status of the current path
   *  true -> toPackage
   *  false -> toFinalDestination
   *  if either pointer is a nullptr it returns true
   */
  void moveDrone(double dt, bool hasPackage);

  /**
   * @brief Picks up the Drone's package when it has reached it.
   */
  void pickUpPackage();

  /**
   * @brief Drops the Drone's package when it has reached it's destination.
   */
  void dropoffPackage();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Decrements the fee for the current delivery
   * @param dec Amount to decrement the fee
   * @param dt Delta time
   */
  void decrementFee(double dec, double dt);

  /**
   * @brief Resets the current delivery fee and
   * updates totalFee
   */
  void resetFee();

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

 private:
  bool available = false;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  IDroneState* state = nullptr;
  double distanceThisDelivery = 0;
  double timeThisDelivery = 0;
  double feeThisDelivery = MAX_FEE;
  double totalFee = 0;
};

#endif
