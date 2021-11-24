#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport_5.h"

Airport_5::Airport_5()
{
    initialize();
    runway = new Runway(queue_limit);
}

Airport_5::Airport_5(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : Airport{endTime, queueLimit, arrivalRate, departureRate}
{
    runway = new Runway(queue_limit);
}

Airport_5::~Airport_5()
{
    delete runway;
}

void Airport_5::initialize()
{
    cout << "This program simulates an airport with only one runway." << endl
         << "One plane can land or depart in each unit of time." << endl
         << "Each plane arrives has its own fuel level (1 - 5)" << endl 
         << "If fuel level < 1 the plane will be granted to land immediately" << endl ;
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
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

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void Airport_5::run()
{
    int flight_number = 0;

    for (int current_time = 0; current_time < end_time; current_time++)
    {                                                       //  loop over time intervals
        int number_arrivals = random.poisson(arrival_rate); //  current arrival requests
        
        for (int i = 0; i < number_arrivals; i++)
        {
            int fuel_level = random.random_integer(MIN_FUEL,MAX_FUEL);
            Plane current_plane(flight_number++, current_time, Plane_status::arriving, fuel_level);
            if (runway->can_land_for_task_5(current_plane) == crash){
                runway->shut_down(end_time);
            }
            else if (runway->can_land_for_task_5(current_plane) != success)
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
        switch (runway->activity_5(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::land:
            moving_plane.land_for_task_5(current_time);
            break;
        case Runway_activity::takeoff:
            moving_plane.fly(current_time);
            break;
        case Runway_activity::idle:
            run_idle(current_time);
        }
    }
}

void Airport_5::shut_down()
{
    runway->shut_down_task_5(end_time);
}
