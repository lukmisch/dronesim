#include "DataCollection.h"

#include <fstream>
#include <iostream>

DataCollection* DataCollection::instance = nullptr;

DataCollection::DataCollection() {}

DataCollection* DataCollection::getInstance() {
  if (instance == nullptr) {
    instance = new DataCollection();
  }
  return instance;
}

void DataCollection::addDroneTrip(int id, double distance, double time,
                                  double currentTotal) {
  for (int i = 0; i < droneStats.size(); i++) {
    if (droneStats[i].id == id) {
      DroneStats stats = droneStats[i];
      stats.numDeliveries++;
      stats.totalDistance += distance;
      stats.totalTimeDelivering += time;
      stats.totalFee = currentTotal;
      droneStats[i] = stats;
      return;
    }
  }

  // If we get here, we didn't find the drone in the vector
  DroneStats stats(id, distance, time, currentTotal);
  droneStats.push_back(stats);
}

void DataCollection::outputToCSV(std::string filename) {
  std::cout << "Outputting Drone Stats to " << filename << std::endl;
  std::ofstream file;
  file.open(filename);

  file << "id,numDeliveries,totalDistance,averageDistancePerTrip,"
          "totalTimeDelivering,averageSpeed,totalFee,averageFee\n";

  for (int i = 0; i < droneStats.size(); i++) {
    DroneStats stats = droneStats[i];
    file << stats.id << "," << stats.numDeliveries << "," << stats.totalDistance
         << "," << stats.totalDistance / stats.numDeliveries << ","
         << stats.totalTimeDelivering << ","
         << stats.totalDistance / stats.totalTimeDelivering << ","
         << stats.totalFee << "," << stats.totalFee / stats.numDeliveries
         << "\n";
  }

  file.close();
}
