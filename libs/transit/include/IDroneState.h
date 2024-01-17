#ifndef I_DRONE_STATE_H_
#define I_DRONE_STATE_H_

class Drone;

#define MIN_FEE 2.0
#define MAX_FEE 10.0

/**
 * @class IDroneState
 * @brief Interface for drone state classes
 *
 * State type determines the behavior of functions
 */
class IDroneState {
 public:
   /**
   * @brief Drone State constructor
   * @param _drone Pointer to the accompanying drone object
   */
  IDroneState(Drone* _drone) : drone(_drone) {}

  /**
  * @brief Destructor
  */
  virtual ~IDroneState() {}

  /**
  * @brief update drone based on state
  * @param dt Delta time
  * Changes behavior based on state:
  *  idle    -> call getNextDelivery() (or maybe do nothing)
  *  Transit -> Moves drone to package
  *  Deliver -> Moves drone to destination
  */
  virtual void updateDrone(double dt) = 0;

 protected:
  Drone* drone;
  double speedMult;
  double feeDecrement;
};

#endif   // DRONE_STATE_H
