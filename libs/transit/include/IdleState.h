#ifndef IDLE_STATE_H_
#define IDLE_STATE_H_

#include "IDroneState.h"

#include "Drone.h"
/**
 * @class IdleState
 * @brief Idle state object
 *
 * Determines behavior for drones in idle state 
 */
class IdleState : public IDroneState {
 public:
  IdleState(Drone* _drone) : IDroneState(_drone) {
    speedMult = 0;
    feeDecrement = 0;
    drone->setColor("green");
  }

   /**
   * @brief update drone
   * @param dt Delta time
   * call getNextDelivery() (or maybe do nothing)
   */
  void updateDrone(double dt);
};


#endif  // IDLE_STATE_H_
