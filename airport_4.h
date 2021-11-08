#include <iostream>
#include "runway.h"
#include "plane.h"
#include "random.h"
#include "error_code.h"
#include "airport.h"

class Airport_4 : public Airport 
{
    private:
        Runway *arrival_runway;
        Runway *departure_runway ;
        Runway *backup_runway;
    public:
        Airport_4() ;
        Airport_4(int endTime, int queueLimit, double arrivalRate, double departureRate) ;
        ~Airport_4() ;

        void initialize() override;

        void run() override;
        void run_idle(int time, string runway);
        void shut_down() override;

};