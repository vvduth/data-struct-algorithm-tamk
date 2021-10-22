#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport.h"

// airport of task 3 has  one runway that is used for both arrival and one for departure.
// Departure runway can be used to accept arrivals if needed 
class Airport_3 : public Airport
{
private:
    Runway *arrival_runway;
    Runway *departure_runway;

public:
    Airport_3();
    Airport_3(int endTime, int queueLimit, double arrivalRate, double departureRate);
    ~Airport_3();

    void initialize() override;

    void run() override;
    void run_idle(int time, string runway);
    void shut_down() override;
};
