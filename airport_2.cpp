#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport_2.h"

Airport_2::Airport_2()
{
    initialize();

    arrival_runway = new Runway(queue_limit);
    departure_runway = new Runway(queue_limit);
}

Airport_2::Airport_2(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : Airport{endTime, queueLimit, arrivalRate, departureRate}
{
    arrival_runway = new Runway(queue_limit);
    departure_runway = new Runway(queue_limit);
}

Airport_2::~Airport_2()
{
    delete arrival_runway;
    delete departure_runway;
}

void Airport_2::initialize()
{
    cout << "This program simulates an airport with two runways." << endl
         << "One plane can land on arrivals runway and depart on departure runway"
         << "each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? on each runway " << flush;
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
            cerr << "These rates must be nonnegative. " << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 2.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void Airport_2::run()
{
    int flight_number = 0;

    for (int current_time = 0; current_time < end_time; current_time++)
    {                                                       //  loop over time intervals
        int number_arrivals = random.poisson(arrival_rate); //  current arrival requests
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, Plane_status::arriving);
            if (arrival_runway->can_land(current_plane) != success)
                current_plane.refuse();
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

        switch (arrival_runway->activity(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::land:
            moving_plane.land(current_time);
            break;
        case Runway_activity::idle:
            run_idle(current_time);
        }

        switch (departure_runway->activity(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::takeoff:
            moving_plane.fly(current_time);
            break;
        case Runway_activity::idle:
            run_idle(current_time);
        }
    }
}

void Airport_2::shut_down()
{
    cout << "---------------------------------\n";
    cout << "|  Stats for Arrival Runway     |\n";
    cout << "---------------------------------\n";

    arrival_runway->shut_down_3(end_time);

    cout << "---------------------------------\n";
    cout << "| Stats for Departure Runway    |\n";
    cout << "---------------------------------\n";

    departure_runway->shut_down_3(end_time);
}
