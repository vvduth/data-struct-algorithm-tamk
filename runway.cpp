#include <iostream>
#include "runway.h"
#include "plane.h"
#include "error_code.h"
using namespace std;

Runway::Runway(int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait  = 0;
    idle_time = 0 ;
    idle_time_2 = 0 ;
    idle_time_3 = 0 ;
    num_landing_diverted = 0;
    num_takeoff_diverted = 0;
}

Error_code Runway::can_land(const Plane &current)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;
    num_land_requests++;

    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;

    return result;
}

Error_code Runway::can_land_for_task_5(const Plane &current){
    Error_code result;
    if (priority.size() > 1 ) {
        cout << "Too many planes out of fuel, the simulation is going crash" << endl ;
        return crash;
        
    } else if (landing.size() + priority.size() < queue_limit) 
        {
            int fuel_lev = current.getFuelLevel();
            if (fuel_lev <= 1 ){
               result = priority.append(current);
            } else {
                result = landing.append(current);
            }
            
        }
    else
        {result = fail;}
    num_land_requests++;

    if (result != success)
        {num_land_refused++;}
    else
        {num_land_accepted++;}

    return result;

}



Error_code Runway::can_depart(const Plane &current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (takeoff.size() < queue_limit)
        result = takeoff.append(current);
    else
        result = fail;
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}

Runway_activity Runway::activity(int time, Plane &moving)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Runway_activity in_progress;
    if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = Runway_activity::land;
        landing.serve();
    }

    else if (!takeoff.empty())
    {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = Runway_activity::takeoff;
        takeoff.serve();
    }

    else
    {
        idle_time++;
        in_progress = Runway_activity::idle;
    }
    return in_progress;
}


Runway_activity Runway::activity_5(int time, Plane &moving)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Runway_activity in_progress;
     if (!priority.empty()) {
        priority.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = Runway_activity::land;
        priority.serve();
    }
    else if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = Runway_activity::land;
        landing.serve();
    }

    else if (!takeoff.empty())
    {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = Runway_activity::takeoff;
        takeoff.serve();
    }

    else
    {
        idle_time++;
        in_progress = Runway_activity::idle;
    }
    return in_progress;
}

Runway_activity Runway::activity_3(int time, Plane &moving)
/*
Post:  Same functionality as activity, but does not increment idle counter.
       Idle must be incremented externally.
Uses:  class Extended_queue.
*/
{
    Runway_activity in_progress;
    if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = Runway_activity::land;
        landing.serve();
    }

    else if (!takeoff.empty())
     {
         takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
         num_takeoffs++;
         in_progress = Runway_activity::takeoff;
         takeoff.serve();
     }

    else
    {
        in_progress = Runway_activity::idle;
    }
    return in_progress;
}


void Runway::shut_down(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "*********************************************************\n"
         << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to take off "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number landing planes diverted to other runway "
         << num_landing_diverted << endl
         << "Total number taking off planes diverted to other runway "
         << num_takeoff_diverted << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff.size() << endl;
    cout << "Percentage of time runway idle " 
         << 100.0 * ((float)idle_time_3) / ((float)time) << "% " <<  idle_time_3 << " " << time << endl;
    cout << "Average wait in landing queue (maybe -nan if there is no plane take off/land in the simulation ) "
         << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl
         << "Average wait in takeoff queue (maybe -nan if there is no plane take off/land in the simulation ) "
         << ((float)takeoff_wait) / ((float)num_takeoffs)
         << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
         << ((float)num_land_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
         << ((float)num_takeoff_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "**************************************************************" << endl;
}


void Runway::shut_down_task_5(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "*********************************************************\n"
         << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to take off "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number landing planes diverted to other runway "
         << num_landing_diverted << endl
         << "Total number taking off planes diverted to other runway "
         << num_takeoff_diverted << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff.size() << endl;
    cout << "Percentage of time runway idle " 
         << 100.0 * ((float)idle_time) / ((float)time) << "% " <<  idle_time<< " " << time << endl;
    cout << "Average wait in landing queue (maybe -nan if there is no plane take off/land in the simulation ) "
         << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl
         << "Average wait in takeoff queue (maybe -nan if there is no plane take off/land in the simulation ) "
         << ((float)takeoff_wait) / ((float)num_takeoffs)
         << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
         << ((float)num_land_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
         << ((float)num_takeoff_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "**************************************************************" << endl;
}

void Runway::fixDivertedLandingCount()
{
    /*
    Post: Change count so that plane that was diverted to second runway shows correctly and not as 
          refused.
    */
    num_landing_diverted++;
    num_land_refused--;
    return;
}

void Runway::fixDivertedTakeoffCount()
{
    /*
    Post: Change count so that plane that was diverted to second runway shows correctly and not as 
          refused.
    */
    num_takeoff_diverted++;
    num_takeoff_refused--;
    return;
}

void Runway::idle()
{
    idle_time++;
}

void Runway::idle3()
{
    idle_time_3++;
}

void Runway::idle2()
{
    idle_time_2++;
}


Runway_activity Runway::movePlaneToOtherRunway(int time, Plane &moving)
{
    /*
Post: The next plane in queue is removed without counting it as landed or departed.
      This is meant for moving a plane from this runway to second idle one.
*/

    Runway_activity in_progress;
    if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landing_diverted++;
        in_progress = Runway_activity::land;
        landing.serve();
    }

    else if (!takeoff.empty())
    {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoff_diverted++;
        in_progress = Runway_activity::takeoff;
        takeoff.serve();
    }

    else
    {
        idle_time++;
        in_progress = Runway_activity::idle;
    }
    return in_progress;
}

Runway_activity Runway::serveLandingFromOtherRunway(int time, Plane &current)
{
    land_wait += time - current.started();
    num_landings++;
    return Runway_activity::land;
}

Runway_activity Runway::serveTakeoffFromOtherRunway(int time, Plane &current)
{
    takeoff_wait += time - current.started();
    num_takeoffs++;

    return Runway_activity::takeoff;
}


void Runway::shut_down_2(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "*********************************************************\n"
         << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to take off "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number landing planes diverted to other runway "
         << num_landing_diverted << endl
         << "Total number taking off planes diverted to other runway "
         << num_takeoff_diverted << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff.size() << endl;
    cout << "Percentage of time runway idle " 
         << 100.0 * ((float)idle_time_2) / ((float)time) << "% " << endl;
    cout << "Average wait in landing queue (maybe -nan if there is no plane take off/land in the simulation)"
         << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl
         << "Average wait in takeoff queue(maybe -nan if there is no plane take off in the simulation) "
         << ((float)takeoff_wait) / ((float)num_takeoffs) << " " << takeoff_wait 
         << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
         << ((float)num_land_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
         << ((float)num_takeoff_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "**************************************************************" << endl;
}


void Runway::shut_down_3(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "*********************************************************\n"
         << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to take off "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number landing planes diverted to other runway "
         << num_landing_diverted << endl
         << "Total number taking off planes diverted to other runway "
         << num_takeoff_diverted << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff.size() << endl;
    cout << "Percentage of time runway idle " 
         << 100.0 * ((float)idle_time) / ((float)time) << "% " << idle_time << " " << time << endl;
    cout << "Average wait in landing queue (maybe -nan if there is no plane take off/land in the simulation )"
         << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl
         << "Average wait in takeoff queue (maybe -nan if there is no plane take off/land in the simulation )"
         << ((float)takeoff_wait) / ((float)num_takeoffs)
         << " time units" << endl;
    cout << "Average wait in takeoff queue "
         << ((float)num_land_requests) / ((float)time)
         << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
         << ((float)num_takeoff_requests) / ((float)time) 
         << " per time unit" << endl;
    cout << "**************************************************************" << endl;
}