#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport_3.h"

Airport_3::Airport_3()
{
    initialize();

    arrival_runway = new Runway(queue_limit);
    departure_runway = new Runway(queue_limit);
}

Airport_3::Airport_3(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : Airport{endTime, queueLimit, arrivalRate, departureRate}
{
    arrival_runway = new Runway(queue_limit);
    departure_runway = new Runway(queue_limit);
}

Airport_3::~Airport_3()
{
    delete arrival_runway;
    delete departure_runway;
}

void Airport_3::initialize()
{
    cout << "This program simulates an airport with two runways." << endl
         << "One runway is primarily for arrivals and one for departures" << endl
         << "One plane can land on arrivals runway and depart on departure runway"
         << "in each unit of time." << endl
         << "if one runway is idle, the other can be used"
         << "if the arrivals queue is full, the arrivals will be diverted to departures\n";
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? on each runway" << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do
    {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 2.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void Airport_3::run()
{
    int flight_number = 0;

    for (int current_time = 0; current_time < end_time; current_time++)
    {                                                       //  loop over time intervals
        int number_arrivals = random.poisson(arrival_rate); //  current arrival requests
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, Plane_status::arriving);
            if (arrival_runway->can_land(current_plane) != success)
            {
                if (departure_runway->can_land(current_plane) != success)
                {
                    current_plane.refuse();
                }
                arrival_runway->fixDivertedLandingCount();
            }
        }

        int number_departures = random.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, Plane_status::departing);
            if (departure_runway->can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;

        // Now two planes can be moving at the same time, one on each runway

        switch (arrival_runway->activity_3(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::land:
            moving_plane.land(current_time);
            break;
        case Runway_activity::idle:

            // Try to get plane from other runway
            Runway_activity activity = departure_runway->movePlaneToOtherRunway(current_time, moving_plane);

            if (activity != Runway_activity::idle)
            {
                arrival_runway->serveTakeoffFromOtherRunway(current_time, moving_plane);
                moving_plane.fly(current_time);
            }
            else
            {
                arrival_runway->idle3();
                run_idle(current_time, "arrival");
            }
            break;
        }

        switch (departure_runway->activity_3(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::takeoff:
            moving_plane.fly(current_time);
            break;
        case Runway_activity::idle:
            Runway_activity activity = arrival_runway->movePlaneToOtherRunway(current_time, moving_plane);

            if (activity != Runway_activity::idle)
            {
                departure_runway->serveLandingFromOtherRunway(current_time, moving_plane);
                moving_plane.land(current_time);
            }
            else
            {
                departure_runway->idle2();
                run_idle(current_time, "departure");
            }
            break;
        }
    }
}

void Airport_3::run_idle(int time, string runway)
{
    cout << time << ": Runway " << runway << " is idle." << endl;
}

void Airport_3::shut_down()
{
    cout << "---------------------------------\n";
    cout << "|     Stats for Arrival Runway  |\n";
    cout << "---------------------------------\n";

    arrival_runway->shut_down(end_time);

    cout << "---------------------------------\n";
    cout << "|   Stats for Departure Runway  |\n";
    cout << "---------------------------------\n";

    departure_runway->shut_down_2(end_time);
}
