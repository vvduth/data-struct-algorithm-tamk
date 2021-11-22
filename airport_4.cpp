#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport_4.h"

Airport_4::Airport_4()
{
    initialize();

    arrival_runway = new Runway(queue_limit);
    departure_runway = new Runway(queue_limit);
    backup_runway = new Runway(queue_limit);
}

Airport_4::Airport_4(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : Airport{endTime, queueLimit, arrivalRate, departureRate}
{
    arrival_runway = new Runway(queue_limit);
    departure_runway = new Runway(queue_limit);
    backup_runway = new Runway(queue_limit);
}

Airport_4::~Airport_4()
{
    delete arrival_runway;
    delete departure_runway;
    delete backup_runway;
}

void Airport_4::initialize()
{
    cout << "This program simulates an airport with three runways." << endl
         << "One runway is only for arrivals and one only for departures" << endl
         << "One plane can land on arrivals runway and depart on departure runway"
         << "in each unit of time." << endl
         << "the third runway is prioritized for landing" << endl
         << "if the landing queue is empty the third runway can be use for take off"
         << "if the arrivals queue is full, the arrivals will be diverted to departures \n";
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
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 2.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}

void Airport_4::run()
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
                if (backup_runway->can_land(current_plane) != success)
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
            {
                if (backup_runway->can_depart(current_plane) != success)
                {
                    current_plane.refuse();
                }

                departure_runway->fixDivertedTakeoffCount();
            }
                
        }

        Plane moving_plane;

        // Now three planes can be moving at the same time, one on each runway

        switch (arrival_runway->activity(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::land:
            moving_plane.land(current_time);
            break;
        case Runway_activity::idle:
            arrival_runway->idle3();
            run_idle(current_time, "arrival");
            break;
        }

        switch (departure_runway->activity(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
        case Runway_activity::takeoff:
            moving_plane.fly(current_time);
            break;
        case Runway_activity::idle:
            departure_runway->idle2();
            run_idle(current_time, "departure");
            break;
        }

        switch (backup_runway ->activity_3(current_time, moving_plane))
        {
        //             
        case Runway_activity::land:
            moving_plane.land(current_time);
            break;
        case Runway_activity::takeoff:
            {
            //check if arrival runway is empty or not, if no, move the next front plane in the quee to the back up runway and let it land
            //skip the take off
            Runway_activity activity = arrival_runway->movePlaneToOtherRunway(current_time, moving_plane);

            if (activity != Runway_activity::idle)
            {
                backup_runway->serveLandingFromOtherRunway(current_time, moving_plane);
                moving_plane.land(current_time);
            } else {
                moving_plane.fly(current_time);
            }
            }
            break;
        case Runway_activity::idle:
            {
            Runway_activity activity_arrival = arrival_runway->movePlaneToOtherRunway(current_time, moving_plane);
            Runway_activity activity_departure = departure_runway->movePlaneToOtherRunway(current_time, moving_plane);
            if (activity_arrival != Runway_activity::idle)
            {
                backup_runway->serveLandingFromOtherRunway(current_time, moving_plane);
                moving_plane.land(current_time);
            } 
            else if (activity_departure != Runway_activity::idle)
            {
                backup_runway->serveTakeoffFromOtherRunway(current_time,moving_plane);
                moving_plane.fly(current_time);
            } 
            
            else {
                backup_runway->idle();
                run_idle(current_time, "backup");  
            }
            }
            break;
    }
    }
}

void Airport_4::run_idle(int time, string runway)
{
    cout << time << ": Runway " << runway << " is idle." << endl;
}

void Airport_4::shut_down()
{
    cout << "---------------------------------\n";
    cout << "|     Stats for Arrival Runway  |\n";
    cout << "---------------------------------\n";

    arrival_runway->shut_down(end_time);

    cout << "---------------------------------\n";
    cout << "|   Stats for Departure Runway  |\n";
    cout << "---------------------------------\n";

    departure_runway->shut_down_2(end_time);


    cout << "--------------------------------\n";
    cout << "|   Stats for Backup Runway  |\n";
    cout << "--------------------------------\n";

    backup_runway->shut_down_3(end_time);

}
