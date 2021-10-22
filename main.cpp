#include <iostream>
#include "utility.h"
#include "Random.h"
#include "Runway.h"
using namespace std;

void run_idle(int time);
void initialize(int& end_time, int& queue_limit,
    double& arrival_rate, double& departure_rate);

void run_idle(int time)
{
    cout << time << ": Runway is idle." << endl;
}

void initialize(int& end_time, int& queue_limit,
    double& arrival_rate, double& departure_rate)
{
    cout << "This program simulates an airport with only a runway." << endl
        << "One plane can land to depart in each unit of time." << endl
        << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run? " << flush;
    cin >> end_time;
    bool acceptable;
    do
    {
        cout << "Expected number of arrivals per unit time? " << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures er unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;
        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated." << endl;

    } while (!acceptable);
}

int main( ) // Airport simulation program
/* Pre: The user must supply the number of time intervals the simulation is to run, the
expected number of planes arriving, the expected number of planes departing
per time interval, and the maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing the status of
the runway at each time interval, and prints out a summary of airport operation
at the conclusion.
Uses: Classes Runway, Plane, Random and functions run idle, initialize. */
{
 int end time; // time to run simulation
int queue limit; // size of Runway queues
int flight number = 0;
double arrival rate, departure rate;
initialize(end time, queue limit, arrival rate, departure rate);
Random variable; Runway small airport(queue limit);
for (int current time = 0; current time < end time; current time++) {
int number arrivals = variable.poisson(arrival rate);
for (int i = 0; i < number arrivals; i++) {
Plane current plane(flight number++, current time, arriving);
if (small airport.can land(current plane) != success)
current plane.refuse( ); }
int number departures = variable.poisson(departure rate);
for (int j = 0; j < number departures; j++) {
Plane current plane(flight number++, current time, departing);
if (small airport.can depart(current plane) != success)
current plane.refuse( ); }
Plane moving plane;
switch (small airport.activity(current time, moving plane)) {
case land: moving plane.land(current time); break;
case takeoff: moving plane.fly(current time); break;
case idle: run idle(current time); }
}
small airport.shut down(end time);
}