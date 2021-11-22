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
   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   int started() const;
   void setFuelLevel();
   int getFuelLevel() ;

private:
   int flt_num;
   int clock_start;
   int fuel_level;
   Plane_status state;
};
