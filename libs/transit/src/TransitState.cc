#include "TransitState.h"

void TransitState::updateDrone(double dt) {
    drone->moveDrone((dt * speedMult), false);
    if (drone->pathComplete(false)) {
        drone->pickUpPackage();
    }
}
