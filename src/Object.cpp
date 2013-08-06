/*
 *  Object.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/25/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"
#include <iostream>

Object::Object( int type, char *name )
{
	this->type		= type;
	this->name		= name;
	
	size[0]			= .5;
	size[1]			= .5;
	size[2]			= .5;
	
	scale[0]		= 1;
	scale[1]		= 1;
	scale[2]		= 1;
	
	rotate[0]		= 0;
	rotate[1]		= 0;
	rotate[2]		= 0;
	rotate[3]		= 0;
}

Object::~Object()
{
}

/**
 * GETTERS AND SETTERS METHODS
 */
char *Object::getName()
{
	return name;
}

int Object::getType()
{
	return type;
}

int Object::getFrame()
{
	return frame;
}

float *Object::getSize()
{
	return size;
}

float *Object::getColor()
{
	return color;
}

float *Object::getPosition()
{
	return position;
}

float *Object::getRotate()
{
	return rotate;
}

float *Object::getScale()
{
	return scale;
}

float *Object::getCameraLookAt()
{
	return cameraLookAt;
}

float *Object::getCameraUp()
{
	return cameraUp;
}

void Object::setFrame(int frame)
{
	this->frame = frame;
}

void Object::setColor(int r, int g, int b)
{
	color[0] = (float)r/255;
	color[1] = (float)g/255;
	color[2] = (float)b/255;
}

void Object::setSize(float x, float y, float z)
{
	size[0] = x;
	size[1] = y;
	size[2] = z;
}

void Object::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Object::setRotate(float x, float y, float z, float ang)
{
	rotate[0] = x;
	rotate[1] = y;
	rotate[2] = z;
	rotate[3] = ang;
}

void Object::setScale(float px, float py, float pz)
{
	scale[0] = px;
	scale[1] = py;
	scale[2] = pz;
}

//theses 2 just if it's camera type
void Object::setCameraLookAt(float x, float y, float z)
{
	cameraLookAt[0] = x;
	cameraLookAt[1] = y;
	cameraLookAt[2] = z;
}

void Object::setCameraUp(float x, float y, float z)
{
	cameraUp[0] = x;
	cameraUp[1] = y;
	cameraUp[2] = z;
}

/**
 * PUBLIC METHODS
 */
void Object::setVisibility(int frame, bool value)
{
	int intVal = value == true ? 1 : -1;	
	visibility[frame] = intVal;
}

bool Object::isVisibleAt(int frame)
{
	bool	lastValue	= false;
	int		frameAux		= frame;
	
	while (frameAux >= 0) {		
		if(visibility[frameAux] == 1 || visibility[frameAux] == -1)
		{
			lastValue = visibility[frameAux] == 1 ? true : false;
			break;
		}
		frameAux--;
	}
	
	return visibility[frame] == 1 || (visibility[frame] == 0 && lastValue);
}

void Object::build()
{
	
}

void Object::destroy()
{
}

/**
 * PRIVATE METHODS
 */

