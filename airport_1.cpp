#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport_1.h"

Airport_1::Airport_1()
{
    initialize();
    runway = new Runway(queue_limit);
}

Airport_1::Airport_1(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : Airport{endTime, queueLimit, arrivalRate, departureRate}
{
    runway = new Runway(queue_limit);
}

Airport_1::~Airport_1()
{
    delete runway;
}

void Airport_1::initialize()
{
    cout << "This program simulates an airport with only one runway." << endl
         << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run? " << flush;
    cin >> end_time;

    bool acceptable;
    do
    {
        cout << "Expected number of arrivals per unit time? " << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time? " << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void Airport_1::run()
{
    int flight_number = 0;

    for (int current_time = 0; current_time < end_time; current_time++)
    {                                                       //  loop over time intervals
        int number_arrivals = random.poisson(arrival_rate); //  current arrival requests
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, Plane_status::arriving);
            if (runway->can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = random.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, Plane_status::departing);
            if (runway->can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        switch (runway->activity(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::land:
            moving_plane.land(current_time);
            break;
        case Runway_activity::takeoff:
            moving_plane.fly(current_time);
            break;
        case Runway_activity::idle:
            run_idle(current_time);
        }
    }
}

void Airport_1::shut_down()
{
    runway->shut_down(end_time);
}
