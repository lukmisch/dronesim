# Drone Simulation

## Our Team

Team Number: 010-83

- Ethan Lynch
- Xavier Lopez
- Luke Mische 
- Daryl Yap

## About The Project

![Website Picture][web-screenshot]

## Project Presentation
[Video of Project Presentation](https://www.youtube.com/watch?v=WuetCTNz_KU)

## Getting Started

### Installation & Setup

1. Clone the repo
    ```sh
    git clone https://github.umn.edu/umn-csci-3081-f23/team-010-83-hw4
    ```

2. Compile the project
    ```sh
    make -j
    ```

### Usage
1. Start the server on port 8081
    ```sh
    make run
    ```

2. Navigate to [localhost:8081](http://localhost:8081) on your web browser

3. From that web page you can access the simulation. Use the schedule page
    to request a delivery.

### Docker
We dockerized this project!

Use this command in your terminal to run the project instead of installing and running
```sh
docker run -it -p 8081:8081 lukmisch/drone_sim
```

## What Does The Simulation Do?

This project simulates a drone delivery system, where drones will fly around the area around and adjacent to the University of Minnesota, pick up packages, and deliver them to robot customers.

Drones can use different routing strategies once they have picked up their package, including A-Star, Beeline, BFS, DFS, and Djikstra's. Routes for algorithms that aren't Beeline strategy are preterdmined and already implemented on the map.

Drones have multiple states that will determine their current responsibilities (extension 1).

Drone statistics can also be tracked and output to CSV files to view data like distance travelled, number of trips made, total delivery fees collected, etc (extension 2).

The Simulation Model has a UI that allows interaction with the simulation to manage/schedule package deliveries by choosing a pickup location and dropoff location via a scheduling page.

Additionally, a celebration decorator has been implemented so that entities jump or spin when their packages are delivered. Other assets have also been utilized in this project, including a helicopter that flies around the map, and humans that will walk along routes.

## Extensions

### Drone State (State Pattern)

![UML for drone state][state-uml]

#### How drone state is determined and possible drone states
Drone state is determined based on the current relation between the drone and its package.
- Idle State      -> drone does not currently have a package to collect nor trasport
- Transport state -> drone is on its way to collect the package
- Deliver state   -> drone is transporting the package to its final destination

#### What does it do?
Drone state determines the current attributes (color and speed) and update behavior of the drone object based on delivery status.
The drone also dynamically calculates a fee based on the duration that it's in the delivery state.
This fee is calculated such that the longer the drone takes to deliver a package, the lower the delivery fee.

#### Why is it significantly interesting?
It provides an additional metric, in the form of the dynamic fee, which adds another layer of realism to the drone simulation. 
The modification of the drone attributes (mainly color) during runtime allows for the user to more easily track the current state of all drones in the simulation.  

#### How does it add to the existing work?
In addition to what was mentioned above, drone states allow for an easier implementation of new states to the drone sim as only a new state class needs to be created.

As the behaviors of the states are largely contained within their implementations (.cc files), drone states also allow for the reduced conditional complexity of certain functions, namely update, making the code more maintainable and readable. 

#### Which design pattern did you choose to implement it and why?
The state pattern was used for this implementation of drone state as it segregated behaviors into seperate 'drone state' classes. 
This meant that we could implement dynamic fees and changing attributes without the additional conditional overhead that would have come from a non-state implementation. 
Additionally, since we are tracking the drone's status based on runtime information (package status), we can more easily swap behaviors using state as it only requires a change in state object. 


### Data Collection (Singleton Pattern)

![UML for data collection][data-collection-uml]

#### Metrics Tracked
1. Number of deliveries for each drone.
2. Total distance traveled by all drones.
3. Average distance traveled per trip.
4. Total time spent on deliveries.
5. Average speed of all drones.
6. Total accumulated delivery fees.
7. Average delivery fee.

#### What does it do?
It collects the aforementioned statistics for all the drones. The stats can be exported through the web page to a CSV file for drone analysis. 

#### Why is it significantly interesting?
It allows the user to see the performance of drones. Possible examples:
 - The data can show the average speed of the drones. So, if a drone is flying too slow, it could be repaired or replaced with a new one. 
 - We can also track the average distance of travel for the drone. This is useful to see how far drones travel in a trip, and maybe plan the battery usage (not implemented in our extension) accordingly.

#### How does it add to the existing work?
It extends the drone's functionality to include statistics of its performance. This allows the users of the simulation to know more about how the drones are performing. 

#### Which design pattern did you choose to implement it and why?
The Singleton Pattern was chosen for this implementation. The Singleton Pattern ensures that a class has only one instance and provides a global point of access to that instance. This is crucial for our data collection, as it guarantees that all drones utilize the same data collection instance, preventing data discrepancies and ensuring consistency. The global point of access allows the user to export the CSV from the web page with ease.  

#### Instruction to use this new feature
1. **Simulation Start:** Begin by simulating the drones with packages until you are ready to export the drone stats.     

2. **Export Drone Stats:**
   - On the simulation web page, locate and click the button labeled "Export Drone Stats."
   - This action triggers the Singleton Pattern for Data Collection to compile the tracked metrics.
   - A CSV file named "drone_stats.csv" is created in the project's root directory.
    - <em> **Note:** If there are any drones currently delivering a package, their data will not be included in the CSV file until the delivery is completed. This ensures accurate and complete metrics for analysis. </em>

3. **Analysis:**
   - The generated "drone_stats.csv" file can be analyzed with spreadsheet software (e.g., Microsoft Excel, Google Sheets).
   - Open the CSV file to review and analyze the performance metrics of the drones, including the number of deliveries, total distance traveled, average distance per trip, total time delivering, and average speed.
   
## Sprint Retrospective

One of the cornerstones of our triumphs during this sprint lies in the meticulous planning and execution of our project schedule. The scheduling strategy implemented was a testament to the collective wisdom and experience of our team. From the outset, we recognized the importance of balancing ambition with feasibility, ensuring that the set timelines were challenging yet realistic for each of our group members. The well-thought-out pacing of our tasks played a pivotal role in maintaining a steady and sustainable workflow. The team demonstrated an acute awareness of project milestones and deadlines, allowing us to navigate the sprint with precision and foresight. This conscientious approach not only prevented unnecessary stress and burnout but also facilitated a more nuanced and thoughtful exploration of the intricacies within our drone delivery simulation.

By delegating our first sprint primarily to setup, including the creation of .h and .cc files, we were able to establish a good foundation for our project early in the timeline. Then, when it came time for our second sprint, we were able to focus on testing, documentation, and the other miscallenous tasks that would wrap our project together.

While acknowledging our accomplishments, it is equally important to identify areas where we can enhance our performance in future sprints. One aspect that deserves attention is the continuous improvement of communication channels. Despite the overall success in work dispersal, there were instances where clearer communication could have averted minor hiccups. Strengthening our communication practices will undoubtedly contribute to even greater cohesion and efficiency in future endeavors.

Discord messaging served as a quick and accessible channel for team communication, fostering real-time exchanges that were integral to our workflow. However, the limitations of text-based communication became apparent when grappling with intricate software concepts. The nuanced nature of these discussions often required more in-depth explanations, visual aids, or interactive discussions that text messages alone could not fully encapsulate.

The intricate details of software development, especially in a simulation project of this magnitude, demand a level of clarity that text messages might not always convey. Complex algorithms, architectural diagrams, and coding intricacies can be challenging to articulate effectively through written communication alone. This limitation occasionally resulted in a lack of clarity, leading to misunderstandings and potential inefficiencies in our collaborative efforts.

In the future, implementing more scheduled voice meetings or in-person meetings, whether through Discord voice channels or other conferencing tools, can provide a platform for more interactive discussions. Verbal communication allows for immediate clarification and a deeper exploration of intricate concepts, and will help us streamline communication of complex coding concepts that may have hindered us over the course of this project.

[web-screenshot]: images/screenshot.jpg
[state-uml]: images/state-uml.jpeg
[data-collection-uml]: images/data-collection-uml.jpeg
[video]: https://www.youtube.com/watch
