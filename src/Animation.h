/*
 *  Animation.h
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Object.h"

class Animation
{
public:
	static const int TRANSLATE	= 0;
	static const int LOOKAT		= 1;
	static const int ROTATE		= 2;
	static const int SCALE		= 3;
	static const int UP			= 4;
	
	Animation(Object *target, int animationType, map<int, float> endValues, int startFrame, int endFrame, int easeType = 0);	
	void run(int currentFrame);
	
	int getStartFrame();
	int getEndFrame();
	int getId();
	void setAuxValues(map<int, float> auxValues);
	
private:
	static int instCount;
	Object *target;
	int id;
	int startFrame;
	int endFrame;
	int totalFrames;
	int easeType;
	int animationType;
	map<int, float> auxValues;
	map<int, float> startValues;
	map<int, float> endValues;
	
	void translate(float u);
	void lookat(float u);
	void rotate(float u);
	void scale(float u);
	void up(float u);
	
	float ease(int index, float u);
};
