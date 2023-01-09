#pragma once
#include <cmath>
#include <iostream>

/*
=========================================================================================
Vector3 - Represents a basic 3-dimensional vector that can be used in a virtual space.
		  This vector is right-handed with z axis pointing upwards, x pointing forwards,
		  and y pointing to the left.
=========================================================================================
*/
class Vector3 {
public:
	Vector3();
	Vector3( const float xAssign, const float yAssign, const float zAssign );

	float		Dot( const Vector3& in );
	void		Cross( const Vector3& in, Vector3& out );
	float		Normalize();
	int			LeftOrRightOfView( const Vector3& position, const Vector3& orientation );
	float		Magnitude();
	void		ScalarMultiply( const float multiplier );
	float		Distance( const Vector3& other );
	void		AddVector( const Vector3& in );
	void		SubtractVector( const Vector3& in );
	bool		AreParallelOrAntiparallel( const Vector3& vec1, const Vector3& vec2 );
	bool		Equals( const Vector3& other );

	float		x;			// Vector X Component.
	float		y;			// Vector Y Component.
	float		z;			// Vector Z Component.
};