#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

#include <string>
#include <vector>

/**
 * @brief Struct to hold drone stats
 *
 */
struct DroneStats {
 public:
  /**
   * @brief Construct a new Drone Stats object
   *
   * @param id Drone ID
   * @param distance Distance traveled this trip
   * @param time Time spent delivering this trip
   * @param fee Current total fee this trip
   */
  DroneStats(int id, double distance, double time, double fee)
      : id(id),
        numDeliveries(1),
        totalDistance(distance),
        totalTimeDelivering(time),
        totalFee(fee) {}

  int id;
  int numDeliveries;
  double totalDistance;
  double totalTimeDelivering;
  double totalFee;
};

/**
 * @class DataCollection
 * @brief Singleton class to collect drone stats
 *
 * Collects drone stats and outputs them to a CSV file
 *
 */
class DataCollection {
 public:
  /**
   * @brief Get the singleton instance object
   *
   * @return DataCollection*
   */
  static DataCollection* getInstance();

  /**
   * @brief Add a drone trip
   *
   * @param id Drone ID
   * @param distance Distance traveled this trip
   * @param time Time spent delivering this trip
   * @param currentTotal Current total fee this trip
   */
  void addDroneTrip(int id, double distance, double time, double currentTotal);

  /**
    * @brief Output drone stats to CSV
    *
    * @param filename Filename to output to
    */
  void outputToCSV(std::string filename);

 private:
  /**
   * @brief Default constructor for the DataCollection object
   *
   */
  DataCollection();

 private:
  static DataCollection* instance;
  std::vector<DroneStats> droneStats;
};

#endif  // DATA_COLLECTION_H_
