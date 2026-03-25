#include "Vector3.h"
#include <cmath>

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::Normalized()
{
	if (abs(this->x) > 1)
	{
		this->x /= abs(this->x);
	}
	if (abs(this->y) > 1)
	{
		this->y /= abs(this->y);
	}
	if (abs(this->z) > 1)
	{
		this->z /= abs(this->z);
	}
	return Vector3(this->x, this->y, this->z);
}