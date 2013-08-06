/*
 *  Object.h
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/25/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <map>
#include <string>

using namespace std;

class Object
{
public:
	static const int BOX		= 0;
	static const int SPHERE		= 1;
	static const int CONE		= 2;
	static const int CYLINDER	= 3;
	static const int CAMERA		= 4;
	
	Object( int type, char *name );
	~Object();
	
	char	*getName();
	int		getType();
	int		getFrame();
	float	*getSize();
	float	*getColor();
	float	*getPosition();
	float	*getRotate();
	float	*getScale();
	float	*getCameraLookAt();
	float	*getCameraUp();

	bool isVisibleAt(int iniframe);
	void setFrame(int frame);
	void setColor(int r, int g, int b);
	void setPosition(float x, float y, float z);
	void setRotate(float x, float y, float z, float ang);
	void setScale(float px, float py, float pz);
	void setCameraLookAt(float x, float y, float z);
	void setCameraUp(float x, float y, float z);
	void setSize(float x, float y, float z);
	void setVisibility(int frame, bool value);
	
	void build();
	void destroy();
	void draw();
	
private:
	map<int, int> visibility;
	
	char		*name;
	int			type;
	int			frame;
	
	float		size[3];
	float		color[3];
	float		position[3];
	float		rotate[4];
	float		scale[3];
	float		cameraLookAt[3];
	float		cameraUp[3];
};
#endif