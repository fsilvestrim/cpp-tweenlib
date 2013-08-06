/*
 *  Easing.h
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

class Easing 
{
public:
	static const int LINEAR			= 100;
	static const int BEZIER			= 101;
	static const int CATMULL_ROM	= 102;
	
	static float linear (float p0, float p1, float t);
	static float bezier (float p0, float p1, float p2, float p3, float t);
	static float catmull_rom (float p0, float p1, float p2, float p3, float t);
};