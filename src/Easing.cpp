/*
 *  Easing.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <cmath>
#include "Easing.h"

float Easing::linear (float p0, float p1, float t)
{
	return (p0 + t * (p1 - p0));
}

float Easing::bezier (float p0, float p1, float p2, float p3, float t)
{
	return (pow((1 - t), 2) * p0 + 2 * t * (1 - t) * p1 + pow(t, 2) * p2);
	//return p0(-t^3 + 3t^2 - 3t + 1) + p1(3t^3 - 6t^2 + 3t) + p2(-3t^3 + 3t^2) + p3(t^3);
}

float Easing::catmull_rom (float p0, float p1, float p2, float p3, float t)
{
	return (0.5 * ((2 * p1) + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * pow(t, 2) + (-p0 + 3 * p1 - 3 * p2 + p3) * pow(t, 3)));
}