#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	// Attributes
	float x;
	float y;
	float z;

	// Functions
	Vector3 Normalized();
private:
	Vector3();
	Vector3(float x, float y, float z);

	
};

#endif

