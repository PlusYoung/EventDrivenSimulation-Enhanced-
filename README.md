# EventDrivenSimulation-Enhanced-
This project will involve implementation of an event-driven simulation of traffic flow through a 4-way intersection that is managed by a traffic light. Your simulation will include cars arriving at the intersection traveling in all four
directions, as well as the light changing state throughout the simulation. After the simulation is complete, you will output some (very minimal) statistics about the traffic flow.

## Detailed Description:
This project will be split up into two phases. It is very strongly recommended that you perform phase 1 fully,
including exhaustive testing, before moving on to work on phase 2.
### Phase 1:
In phase 1, you will update some of the data structures you developed in project 4 to be “templated” – that is, to be
associated with a generic data type using C++ templates such that the data structures are able to hold more data
types than just integers.
The SortedListClass and the FIFOQueueClass must be modified to be templated classes. There is no need to use the
LIFOStackClass in this project, so it is not required that you make it a templated class or include it in your
submission.The design, names and functional interface to your templated data structure classes must match those developed
in project 4 exactly. In other words, you may not add new member functions, add new member variables, change
the number or meaning of function parameters, etc. The only difference between the data structures developed in
project 4 and the modified versions developed in project 5 will be that the project 4 versions are specifically tied to
integers, while the project 5 versions are templated.
Phase 1 of this project should NOT result in writing much “new code”, except for developing test cases to make
sure your updated data structures work with different data types.
### Phase 2:
Once your data structures are implemented and tested, you will develop an event-driven simulation of cars
traveling through an intersection that is managed by a functioning traffic light. Events are a central part of an
event-drive simulation, so you will need an EventClass. As discussed in lecture, event objects will be stored in a
SortedListClass that is referred to as “the event list”. The event list will only contain events that are scheduled to
occur in the future – it will NOT store events that have already been handled.
Concept of “Time Tics”
A “time tic” is a unit-less measure of time. When we say something occurs in “3 time tics” is just means 3
advancements of time. It might be 3 seconds, or 3 minutes, or 3 milliseconds, etc. The point is that a “time tic” is
just meant to represent a generic unit of time so that we don’t have to think in terms of specific units of time. This
is often convenient to allow simulations to “scale” as needed – I might set my simulation parameters in a way that I
think of a “time tic” as being milliseconds, but another user might set their simulation parameters in a way that
they think of a “time tic” as seconds.
#### Simulation Parameters and Input File Format
There are 15 control parameters that will affect how the simulation performs. To make it easy to run many
different simulations, the simulation control parameters will be read from a text file, whose name will be provided
to the program via a command line argument. The parameters are as follows:
- Random number generator seed: A non-negative integer value for seeding the random number generator
to select a pseudo-random sequence for the simulation to use.
- Simulation end time: A positive integer value indicating when the simulation should end. When the next
event occurs after this specified number of time tics, the event, and any scheduled after it will not be
handled, and the simulation will be deemed completed.
- East-west green time and east-west yellow time: Two positive integers indicating the amount of time the
light is green and yellow in the east-west direction. Red duration is NOT specified, as it is assumed to be
the sum of the green and yellow times for the north-south direction.
- North-south green time and north-south yellow time: Two positive integers indicating the amount of time
the light is green and yellow in the north-south direction. Red duration is NOT specified, as it is assumed to
be the sum of the green and yellow times for the east-west direction.
- Mean and standard deviation for the arrival rate of east-bound cars: Two positive floating point values
indicating the mean and standard deviation of the pre-determined normal distribution characterizing the
arrival rate for cars arriving at the intersection in an east-bound direction.
- Mean and standard deviation for the arrival rate of west-bound cars: Two positive floating point values
indicating the mean and standard deviation of the pre-determined normal distribution characterizing the
arrival rate for cars arriving at the intersection in an west-bound direction.• Mean and standard deviation for the arrival rate of north-bound cars: Two positive floating point values
indicating the mean and standard deviation of the pre-determined normal distribution characterizing the
arrival rate for cars arriving at the intersection in an north-bound direction.
- Mean and standard deviation for the arrival rate of south-bound cars: Two positive floating point values
indicating the mean and standard deviation of the pre-determined normal distribution characterizing the
arrival rate for cars arriving at the intersection in an south-bound direction.
- Percentage of drivers that will advance through a yellow light: An integer value from 0 to 100 (inclusive)
describing how often a driver will choose to advance through the intersection when the light is yellow. A
number of 40 indicates that 40% of the time a driver will choose to advance through a yellow light, while
60% of the time a driver will choose to stop at the yellow light.

#### Event Handling Overview
The most important part of an event-driven simulation is the handling of events. As discussed in lecture, handling
an event will often generate additional events to be scheduled to occur in the future. Additionally, handling an
event will often change the state of the simulation (i.e. advance the simulation’s “current time” to the time the
event being handled at occurs, etc.), and will often change accumulating statistics (like maximum values, counts of
objects, etc.).


To keep our simulation less complex, we will implement the cars advancing through an intersection only when the
light is changing. Obviously, this is not realistic – in the “real world” cars advance through the intersection while
the light is green (or yellow). We will handle this differently though.



Specifically, let’s say the light is green in the north-south direction for 10 time tics. When we handle an event that
represents a change in the light to being yellow in the north-south direction, we will implement the logic to 
advance up to 10 cars in the north-bound queue to travel through the intersection and up to 10 cars in the southbound queue to travel through the intersection. The idea behind this is that when a light is changing to yellow, all the cars that would want to advance through the intersection on the green light will have arrived and be placed in
the queues. So it is during the handling of the change to yellow that we advance the cars for the green light. That
might seem odd at first, but it makes the processing much simpler, so take a minute to understand what is
expected, and look at the sample output to make sure you understand the proper flow of the simulation.
Similarly, when we handle an event representing the light changing from yellow in the north-south direction to
green in the east-west direction, that is when we will advance cars through the intersection in the north-south
direction for the yellow light that is changing.

#### Light Cycle
The light will always start as a green light in the east-west direction for our simulation!
The traffic light cycles as follows:
| Current Light State | Changed Light State | Cars Advancing During Change Event Handling |
|---------------------|---------------------|--------------------------------------------|
| Green East-West     | Yellow East-West    | East-West traffic through green light       |
| Yellow East-West    | Green North-South   | East-west traffic through yellow light      |
| Green North-South   | Yellow North-South  | North-south traffic through green light     |
| Yellow North-South  | Green East-West     | North-south traffic through yellow light    |


When advancing cars through a green light, cars advance one-per-time-tic. A green light that lasts for 20 time tics
will allow up to 20 waiting cars in both directions to advance.


When advancing cars through a yellow light, you must consider that some drivers will advance through a yellow
light, but others will stop at the light. For our simulation, we will determine a driver’s decision using a uniform
random number such that a specified percentage of drivers will be expected to advance through the light and the
remainder will be expected to stop. Obviously, if a driver decides to stop at the yellow light, cars that are behind it
will be forced to stop as well. Let’s say the simulation parameter that controls this is set to 75. This would mean
that 75% of drivers will advance through the yellow light, while 25% will choose to stop at the light. If you request a
uniform random number between 1 and 100, you can determine the driver will advance if the random number is
less than or equal to 75, while a result greater than 75 will indicate the driver will NOT advance through the light.
This is just an example, and you would instead compare your uniform random number to the corresponding
simulation control parameter instead of always using the literal value 75. If a driver decides to advance through a
yellow light, the following driver will make their own decision, so you’ll draw another uniform random number as
needed for that driver, and so on.


#### Event Handling Specifics
There are 8 types of events that can occur in our simulation.
• Car arrival east-bound (EVENT_ARRIVE_EAST)
  - When handling an event of a car arriving at the intersection heading east, it gets added to the eastbound queue of cars waiting to get through the intersection. The next east-bound arrival event isalso scheduled during the handling of this type of event, based on the east-bound arrival
distribution parameters (mean and standard deviation).
• Car arrival west-bound (EVENT_ARRIVE_WEST)
  - Same as “Car arrival east-bound” but for a west-bound car instead.
• Car arrival north-bound (EVENT_ARRIVE_NORTH)
  - Same as “Car arrival east-bound” but for a north-bound car instead.
• Car arrival south-bound (EVENT_ARRIVE_SOUTH)
  - Same as “Car arrival east-bound” but for a south-bound car instead.
• Light change from “Green in East-West” to “Yellow in East-West” (EVENT_CHANGE_YELLOW_EW)
  - When the light changes FROM a green light in the east-west direction TO a yellow light in the eastwest direction, you will advance cars through the intersection for the green light in the east-west
direction. If the light is green in the east-west direction for 10 time tics, then when handling this
event type, you will allow up to 10 cars waiting in the east-bound queue to advance through the
intersection (or less than 10 if there are less than 10 cars waiting in the queue), and up to 10 cars
waiting in the west-bound queue to advance through the intersection. Finally, you’ll also schedule
the next light change event to occur at the appropriate time in the future (the next light change
event in this case would be a light change from “Yellow in East-West” to “Green in North-South”.
• Light change from “Yellow in East-West” to “Green in North-South” (EVENT_CHANGE_GREEN_NS)
  - Advance cars through the intersection for the yellow light in the east-west direction, and schedule
the next light change (from “Green in North-South” to “Yellow in North-South”
• Light change from “Green in North-South” to “Yellow in North-South” (EVENT_CHANGE_YELLOW_NS)
  - Advance cars through the intersection for the green light in the north-soth direction, and schedule
the next light change (from “Yellow in North-South” to “Green in East-West”
• Light change from “Yellow in North-South” to “Green in East-West” (EVENT_CHANGE_GREEN_EW)
  - Advance cars through the intersection for the yellow light in the north-south direction, and
schedule the next light change (from “Green in East-West” to “Yellow in East-West”
#### Design and Provided Code
##### EventClass
I will provide most of the EventClass for you to use in your project. Since objects of the EventClass will be stored in
a SortedListClass (which was templated in phase 1), you will need to update the EventClass to overload any
operators that are used on the templated type within your SortedListClass. EventClass objects are sorted based on
their scheduled time to occur. So, for example, an event scheduled to occur at time 5 will come before an event
scheduled to occur at time 7 in your sorted event list.
##### CarClass
I will provide a CarClass for you to use in your project. The concept of a “car object” in this project isn’t meant to
describe the car itself (i.e. the color, make, model, number of doors, etc.), but rather to maintain some data about a
car that is participating in our simulation. Therefore, you’ll see the CarClass attributes include a unique identifier
value (auto-assigned in the primary ctor), the direction the car is going as it approaches the intersection, and the
time at which it arrived at the intersection.
##### IntersectionSimulationClass
This is the “over-arching” class for the project. It will be the class that stores the control parameters of the
simulation, advances the state of the simulation as it runs, and maintains statistics about the simulation as it runs.
It will contain the all-important event list containing all events currently scheduled, as well as queues of vehicles
awaiting their turn to advance through the intersection.I will provide a portion of the IntersectionSimulationClass for you to use. The provided code will include the class
attributes, the functionality to read simulation parameters from an input file, and print the final statistics. You will
need to add functionality to this class, though, to actually handle events appropriately and maintain the statistics
values throughout.
##### constants.h
I will provide a set of pre-defined constants for your use in this project. Of course, if you want to add additional
constants to this file, you may do so. I did not “hide” any of my constants from you, so I don’t anticipate you
needing to add constants, but if your implementation would benefit from additional constants, that is fine.
##### random.h and random.cpp
These files contain some high-level functionality to obtain random numbers according to either a uniform
distribution or a normal distribution. You may NOT modify these functions. You can use them as provided.
##### project5.cpp
This is the main function for the project. I will provide my solution’s entire main function for you to use. You
should not need to modify the provided project5.cpp, but you may make minor modifications if for some reason
you find that you need to in your implementation. If you find you need to modify it, though, you may want to
consult with the course staff to make sure the high-level design is proper.

