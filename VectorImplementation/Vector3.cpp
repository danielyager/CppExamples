#include "Vector3.h"

/*
================================================
Vector3 Constructor - No Arguments
================================================
*/
Vector3::Vector3() {
	Vector3(0.0, 0.0, 0.0);
}

/*
================================================
Vector3 Constructor - All Arguments
================================================
*/
Vector3::Vector3( const float xAssign, const float yAssign, const float zAssign ) {
	x = xAssign;
	y = yAssign;
	z = zAssign;
}

/*
=======================================================
Vector3::Dot - Calculates and returns the dot product
			   between this vector and another passed
			   as a paramter.
=======================================================
*/
float Vector3::Dot( const Vector3& in ) {
	return x * in.x + y * in.y + z * in.z;
}

/*
=======================================================
Vector3::Cross - Calculates the cross product of two
				 vectors passed as parameters "in" and
				 "out". The result is assigned to the
				 out parameter.
=======================================================
*/
void Vector3::Cross( const Vector3& in, Vector3& out ) {
	out = Vector3(y * in.z - z * in.y, z * in.x - x * in.z, x * in.y - y * in.x);
}

/*
========================================================
Vector3::Normalize - Converts this vector to a unit
					 vector. Giving it a magnitude of 1.
========================================================
*/
float Vector3::Normalize() {
	const float sqrLength = x * x + y * y + z * z;
	const float invLength = 1.0f / sqrtf(sqrLength);
	x *= invLength;
	y *= invLength;
	z *= invLength;
	return invLength * sqrLength;
}

/*
===================================================================================
Vector3::LeftOrRightOfView

This method takes two Vector3 objects as paramters (position and orientation).
The input paramters represent the location and orientation of a camera's view.
The method returns whether this Vector3 object (interpreted here as a position)
is sitting to the left or right of the camera's view (or unknown).

Returns:
 1	- Sitting to the right of the camera's view.
-1	- Sitting to the left of the camera's view.
 0	- Unknown (This will happen if the point is directly in front of or behind
	  the camera's view, along with if the camera is looking directly upward on
	  the z axis.
===================================================================================
*/
int Vector3::LeftOrRightOfView( const Vector3& position, const Vector3& orientation ) {
	Vector3 positionRelativeToCamera = Vector3(x - position.x, y - position.y, z - position.z);

	// Return 0 if vectorRelativeToPosition is parallel or anti-parallel to orientation.
	if (AreParallelOrAntiparallel(positionRelativeToCamera, orientation)) {
		return 0;
	}

	positionRelativeToCamera.Cross(orientation, positionRelativeToCamera);
	Vector3 upVector = Vector3(0.0f, 0.0f, 1.0f);
	float dotProduct = upVector.Dot(positionRelativeToCamera);

	// Returns information on whether vector is left, right, or neither/unknown.
	// -1	= to the left
	// 1	= to the right
	// 0	= neither/unknown.
	if (dotProduct < 0) {
		return -1;
	} else if (dotProduct > 0) {
		return 1;
	} else {
		return 0;
	}
}

/*
=======================================================
Vector3::Magnitude - Returns the length of the vector.
=======================================================
*/
float Vector3::Magnitude() {
	return sqrtf((x * x) + (y * y) + (z * z));
}

/*
=========================================================
Vector3::ScalarMultiply - Multiplies the elements of the
						  vector by some scalar value
						  given as a parameter.
=========================================================
*/
void Vector3::ScalarMultiply( const float multiplier ) {
	x *= multiplier;
	y *= multiplier;
	z *= multiplier;
}

/*
=================================================================
Vector3::Distance - Calculates the distance between two vectors.
=================================================================
*/
float Vector3::Distance( const Vector3& other ) {
	float distanceX = x - other.x;
	float distanceY = y - other.y;
	float distanceZ = z - other.z;
	return sqrtf((distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ));
}

/*
=================================================================
Vector3::AddVector - Takes a Vector3 object as a parameter
					 and adds it, elementwise, from this vector.
=================================================================
*/
void Vector3::AddVector( const Vector3& in ) {
	x += in.x;
	y += in.y;
	z += in.z;
}

/*
================================================================
Vector3::SubtractVector - Takes a Vector3 object as a parameter
						  and subtracts it, elementwise, from
						  this vector.
================================================================
*/
void Vector3::SubtractVector( const Vector3& in ) {
	x -= in.x;
	y -= in.y;
	z -= in.z;
}

/*
===========================================================
Vector3::AreParallelOrAntiparallel

Compares two input Vector3 parameters and returns true if
they are parallel or anti-parallel to each other.
False otherwise.
===========================================================
*/
bool Vector3::AreParallelOrAntiparallel( const Vector3& vec1, const Vector3& vec2 ) {
	Vector3 tempVec1 = Vector3(vec1.x, vec1.y, vec1.z);
	Vector3 tempVec2 = Vector3(vec2.x, vec2.y, vec2.z);

	tempVec1.Normalize();
	tempVec2.Normalize();

	if (tempVec1.Equals(tempVec2)) {
		return true;
	} else {
		tempVec2.ScalarMultiply(-1.0f);
		return tempVec1.Equals(tempVec2);
	}
}

/*
===========================================================
Vector3::Equals - Takes another Vector3 object as a
					parameter and returns true if each
					element between the vectors are equal.
					False otherwise.
===========================================================
*/
bool Vector3::Equals( const Vector3& other ) {
	return ((x == other.x) && (y == other.y) && (z == other.z));
}