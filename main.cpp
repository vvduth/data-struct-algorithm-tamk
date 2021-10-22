#include <iostream>
#include <climits>
#include "airport.h"
#include "airport_1.h"
//#include "airport_2.h"
//#include "airport_3.h"

using namespace std;

int chooseVersion()
{
    int userChoise;

    bool acceptable = false;

    while (true)
    {

        cout << "Welcome to airport simulator.\n "
             << "Please choose the version you would like to run\n"
             << "1: task 1: single shared runway\n"
             << "2: task 2: separate runways for arrival and departure\n"
             << "3: task 3: separate runways for arrival and departure, planes can be moved between\n"
             << "Input: "
             << flush;

        if (cin >> userChoise)
        {
            if (userChoise == 1 || userChoise == 2 || userChoise == 3)
            {
                return userChoise;
            }
        }
        else
        {
            // clear error from cin so it works correctly when asking again.
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }

    return userChoise;
}

int main() //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{
    int version = chooseVersion();
    Airport *airport;
    switch (version)
    {
    case 1:
        airport = new Airport_1();
        break;
    // case 2:
    //     airport = new Airport_2();
    //     break;
    // case 3:
    //     airport = new Airport_3();
    //     break;
    }

    airport->run();
    airport->shut_down();
    delete airport;
}



// #include <iostream>
// #include"Utility.h"
// #include"random.h"
// #include"runway.h"
// #include"plane.h"
// using namespace std;

// void run_idle(int time);
// void initialize(int& end_time, int& queue_limit,
//     double& arrival_rate, double& departure_rate);

// int main()
// {
    
//     Random random;
//     int end_time;
//     int queue_limit;
//     int flight_number = 0;
//     double arrival_rate, departure_rate;

//     initialize(end_time, queue_limit, arrival_rate, departure_rate);

//     Runway small_airport(queue_limit);

//     for (int current_time = 0; current_time < end_time; current_time++)
//     {
//         int number_arrivals = random.poisson(arrival_rate);
//         for (int i = 0; i < number_arrivals; ++i)
//         {
//             Plane current_plane(flight_number++, current_time, Plane_status::arriving);
//             if (small_airport.can_land(current_plane) != success)
//                 current_plane.refuse();

//         }

//         int num_departures = random.poisson(departure_rate);

//         for (int j = 0; j < num_departures; j++)
//         {
//             Plane current_plane(flight_number++, current_time, Plane_status::departing);
//             if (small_airport.can_depart(current_plane) != success)
//                 current_plane.refuse();
//         }

//         Plane moving_plane;
//         switch (small_airport.activity(current_time, moving_plane))
//         {
//         case Runway_activity::land:
//             moving_plane.land(current_time);
//             break;
//         case Runway_activity::takeoff:
//             moving_plane.fly(current_time);
//             break;
//         case Runway_activity::idle:
//             run_idle(current_time);
//         }

//     }
//     small_airport.shut_down(end_time);

//     return 0;
	
// }

// void run_idle(int time)
// {
//     cout << time << ": Runway is idle." << endl;
// }

// void initialize(int& end_time, int& queue_limit,
//     double& arrival_rate, double& departure_rate)
// {
//     cout << "This program simulates an airport with only a runway." << endl
//         << "One plane can land to depart in each unit of time." << endl
//         << "Up to what number of planes can be waiting to land "
//         << "or take off at any time? " << flush;
//     cin >> queue_limit;
//     cout << "How many units of time will the simulation run? " << flush;
//     cin >> end_time;
//     bool acceptable;
//     do
//     {
//         cout << "Expected number of arrivals per unit time? " << flush;
//         cin >> arrival_rate;
//         cout << "Expected number of departures er unit time?" << flush;
//         cin >> departure_rate;
//         if (arrival_rate < 0.0 || departure_rate < 0.0)
//             cerr << "These rates must be nonnegative." << endl;
//         else
//             acceptable = true;
//         if (acceptable && arrival_rate + departure_rate > 1.0)
//             cerr << "Safety Warning: This airport will become saturated." << endl;

//     } while (!acceptable);
// }
