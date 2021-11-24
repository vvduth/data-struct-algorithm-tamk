#pragma once
#include "extended_queue.h"
#include "plane.h"
#include "error_code.h"

enum class Runway_activity
{
    idle,
    land,
    takeoff,
    crash
};

class Runway
{
public:
    Runway(int limit);
    Error_code can_land(const Plane &current);
    Error_code can_land_for_task_5(const Plane &current);
    Error_code can_depart(const Plane &current);
    Runway_activity activity(int time, Plane &moving);
    Runway_activity activity_3(int time, Plane &moving);
    Runway_activity activity_4(int time, Plane &moving);
    Runway_activity activity_5(int time, Plane &moving);
    void shut_down(int time) const;
    void shut_down_2(int time) const;
    void shut_down_3(int time) const ;
    void fixDivertedLandingCount();
    void fixDivertedTakeoffCount();
    void idle();
    void idle2();
    void idle3();
    Runway_activity movePlaneToOtherRunway(int time, Plane &moving);
    Runway_activity serveLandingFromOtherRunway(int time, Plane &moving);
    Runway_activity serveTakeoffFromOtherRunway(int time, Plane &moving);

private:
    Extended_queue landing;
    Extended_queue takeoff;
    Extended_queue priority ;
    int queue_limit;
    int num_land_requests;    //  number of planes asking to land
    int num_takeoff_requests; //  number of planes asking to take off
    int num_landings;         //  number of planes that have landed
    int num_takeoffs;         //  number of planes that have taken off
    int num_land_accepted;    //  number of planes queued to land
    int num_takeoff_accepted; //  number of planes queued to take off
    int num_land_refused;     //  number of landing planes refused
    int num_takeoff_refused;  //  number of departing planes refused
    int land_wait;            //  total time of planes waiting to land
    int takeoff_wait;         //  total time of planes waiting to take off
    int idle_time;            //  total time runway is idle
    int idle_time_2 ;           //task3
    int idle_time_3 ;   ///task3

    int num_landing_diverted; //  number of landing planes diverted to other runway
    int num_takeoff_diverted; //  number of departing planes diverted to other runway
};
