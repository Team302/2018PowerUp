#ifndef LIDAR_I2C
#define LIDAR_I2C

#include <iostream>
#include <wpilib.h>
#include "Lidar.h"

class LidarI2C : public Lidar
{
public:
	LidarI2C(I2C::Port port, char address); // this is the constructor. it is the part of the code that you use to contruct thhis object. it takes int a ITC::Port port, and a char address.
	virtual double GetDistance(); // REturns the distance (unknown units)
	virtual double PIDGet(); // don't use this mehtod
	virtual ~LidarI2C();

private:
	I2C *lidar;
	void ReadyUp();
};

#endif
