#ifndef DELIVER_STATE_H_
#define DELIVER_STATE_H_

#include "IDroneState.h"

#include "Drone.h"
/**
 * @class DeliverState
 * @brief Deliver state object
 *
 * Determines behavior for drones in deliver state 
 */
class DeliverState : public IDroneState {
 public:
  DeliverState(Drone* _drone) : IDroneState(_drone) {
    speedMult = 0.8;
    feeDecrement = 0.05;
    drone->setColor("yellow");
  }

   /**
   * @brief update drone
   * @param dt Delta time
   * move drone and package while not at destination  
   */
  void updateDrone(double dt);
};



#endif  // DELIVER_STATE_H_
