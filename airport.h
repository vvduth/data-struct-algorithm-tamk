#pragma once
#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"


/*
This is a base version of airport class, that is not meant to be used as is. 
Inherit this an implementation airport from this, and specify runways there.
*/
class Airport
{

protected:
    int end_time;
    int queue_limit;
    double arrival_rate;
    double departure_rate;

    Random random;

public:
    Airport();
    Airport(int endTime, int queueLimit, double arrivalRate, double departureRate);
    virtual ~Airport();

    virtual void initialize() = 0;
    virtual void run() = 0;
    virtual void run_idle(int time);
    virtual void shut_down() = 0;
};
