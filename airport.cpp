#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport.h"

Airport::Airport()
    : end_time{1}, queue_limit{1}, arrival_rate{0.1}, departure_rate{0.1}
{
}

Airport::Airport(int endTime, int queueLimit, double arrivalRate, double departureRate)
    : end_time{endTime}, queue_limit{queueLimit}, arrival_rate{arrivalRate}, departure_rate{departureRate}

/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/
{
}

Airport::~Airport()
{
}

void Airport::run_idle(int time)
{
    cout << time << ": Runway is idle." << endl;
}
