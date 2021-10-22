#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport.h"

// airport of task 2 has  one runway that is used for both arrival and one for departure.
class Airport_2 : public Airport
{
private:
    Runway *arrival_runway;
    Runway *departure_runway;

public:
    Airport_2();
    Airport_2(int endTime, int queueLimit, double arrivalRate, double departureRate);
    ~Airport_2();

    void initialize() override;

    void run() override;
    // void run_idle(int time) override;
    void shut_down() override;
};
