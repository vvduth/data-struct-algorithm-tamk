#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport.h"

// airport of task 1 has only one runway that is used for both arrival and departure.
class Airport_1 : public Airport
{
private:
    Runway *runway;

public:
    Airport_1();
    Airport_1(int endTime, int queueLimit, double arrivalRate, double departureRate);
    ~Airport_1();

    void initialize() override;
    void run() override;
    // void run_idle(int time) override;
    void shut_down() override;
};
