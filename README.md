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
