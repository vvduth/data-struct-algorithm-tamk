#pragma once

enum class Plane_status
{
   null,
   arriving,
   departing
};

class Plane
{
public:
   Plane();
   Plane(int flt, int time, Plane_status status);
   Plane(int flt, int time, Plane_status status, int fuel_level_x);
   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   int started() const;
   void setFuelLevel(int fuelLevel);
   int getFuelLevel() const ;

private:
   int flt_num;
   int clock_start;
   int fuel_level;
   Plane_status state;
};
