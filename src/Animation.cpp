/*
 *  Animation.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include "Animation.h"
#include "Easing.h";

int Animation::instCount = 0;

int Animation::getStartFrame ()
{
	return startFrame;
}

int Animation::getEndFrame ()
{
	return endFrame;
}

int Animation::getId ()
{
	return id;
}

void Animation::setAuxValues(map<int, float> auxValues)
{
	this->auxValues = auxValues;
}

Animation::Animation(Object *target, int animationType, map<int, float> endValues, int startFrame, int endFrame, int easeType)
{
	this->id				= ++instCount;
	this->target			= target;
	this->animationType		= animationType;
	this->endValues			= endValues;
	this->startFrame		= startFrame;
	this->endFrame			= endFrame;
	this->easeType			= easeType;
	
	totalFrames = endFrame - startFrame + 1;
}

void Animation::run(int currentFrame)
{
	float u		= (float)(currentFrame - startFrame) / (float)totalFrames;
	
	switch (animationType) 
	{
		case Animation::TRANSLATE:
				translate(u);
			break;
		case Animation::SCALE:
				scale(u);
			break;
		case Animation::ROTATE:
				rotate(u);
			break;
		case Animation::LOOKAT:
				lookat(u);
			break;
		case Animation::UP:
				up(u);
			break;
	}
}

float Animation::ease(int index, float u)
{
	float value = 0;
	
	switch (easeType) {
		case Easing::LINEAR:
			value = Easing::linear(startValues[index], endValues[index], u);
			break;
		case Easing::BEZIER:
			value = Easing::bezier(startValues[index], endValues[index], auxValues[index], auxValues[index+100], u);
			break;
		case Easing::CATMULL_ROM:
			value = Easing::catmull_rom(startValues[index], endValues[index], auxValues[index], auxValues[index+100], u);
			break;
	}
	
	return value;
}

void Animation::translate(float u)
{
	if(u == 0)
	{
		startValues[0] = target->getPosition()[0];
		startValues[1] = target->getPosition()[1];
		startValues[2] = target->getPosition()[2];
	}
	
	float v0	= ease(0, u);
	float v1	= ease(1, u);
	float v2	= ease(2, u);
	
	target->setPosition(v0, v1, v2);
}

void Animation::rotate(float u)
{
	if(u == 0)
	{
		startValues[0] = target->getRotate()[0];
		startValues[1] = target->getRotate()[1];
		startValues[2] = target->getRotate()[2];
		startValues[3] = target->getRotate()[3];
	}
	
	float v0	= ease(1, u);
	float v1	= ease(2, u);
	float v2	= ease(3, u);
	
	target->setRotate(startValues[0], v0, v1, v2);
}

void Animation::scale(float u)
{
	if(u == 0 && startValues[0] != target->getScale()[0])
	{
		startValues[0] = target->getScale()[0];
		startValues[1] = target->getScale()[1];
		startValues[2] = target->getScale()[2];
		
		endValues[0] = endValues[0] * startValues[0];
		endValues[1] = endValues[1] * startValues[1];
		endValues[2] = endValues[2] * startValues[2];
	}
	
	float v0	= ease(0, u);
	float v1	= ease(1, u);
	float v2	= ease(2, u);
	
	target->setScale(v0, v1, v2);
}

void Animation::lookat(float u)
{
	if(u == 0)
	{
		startValues[0] = target->getCameraLookAt()[0];
		startValues[1] = target->getCameraLookAt()[1];
		startValues[2] = target->getCameraLookAt()[2];
	}
	
	float v0	= ease(0, u);
	float v1	= ease(1, u);
	float v2	= ease(2, u);
	
	target->setCameraLookAt(v0, v1, v2);
}

void Animation::up(float u)
{
	if(u == 0)
	{
		startValues[0] = target->getCameraUp()[0];
		startValues[1] = target->getCameraUp()[1];
		startValues[2] = target->getCameraUp()[2];
	}
	
	float v0	= ease(0, u);
	float v1	= ease(1, u);
	float v2	= ease(2, u);
	
	target->setCameraUp(v0, v1, v2);
}


