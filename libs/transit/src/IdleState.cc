#include "IdleState.h"

void IdleState::updateDrone(double dt) {
    // Don't need to check availablity since it's
    // implcitly available if in idle state
    drone->getNextDelivery();
}
