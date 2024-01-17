#ifndef TRANSIT_STATE_H_
#define TRANSIT_STATE_H_

#include "IDroneState.h"

#include "Drone.h"
/**
 * @class TransitState
 * @brief Transit state object
 *
 * Determines behavior for drones in transit state 
 */
class TransitState : public IDroneState {
 public:
  TransitState(Drone* _drone) : IDroneState(_drone) {
    speedMult = 1.5;
    feeDecrement = 0;
    drone->setColor("blue");
  }

   /**
   * @brief update drone
   * @param dt Delta time
   * move drone to package
   */
  void updateDrone(double dt);
};


#endif  // TRANSIT_STATE_H_
