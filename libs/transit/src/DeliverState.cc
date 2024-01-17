#include "DeliverState.h"

void DeliverState::updateDrone(double dt) {
    drone->moveDrone((dt * speedMult), true);
    if (drone->pathComplete(true)) {
        drone->resetFee();
        drone->dropoffPackage();
    } else {
        drone->decrementFee(feeDecrement, dt);
    }
}
