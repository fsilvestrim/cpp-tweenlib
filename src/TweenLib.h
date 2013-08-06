/*
 *  TweenLib.h
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/18/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef TWEENLIB_H
#define TWEENLIB_H

#include <stdio.h>
#include <map>

#include "Object.h"
#include "Animation.h"

using namespace std;

class TweenLib 
{
private:
	static TweenLib *instance;
	
public:
	TweenLib();
	~TweenLib();
	
	int		currentFrame;
	
	static TweenLib *getInstance();
	
	map<char*, Object *> objMap;
	map<char*, Object *>::iterator itObj;
	map<int, Animation *> animMap;
	map<int, Animation *>::iterator itAnim;
	
	void	addObject(Object *obj);
 	Object	*getObject(char *name);
	
	void	addAnimation(Animation *anim);
	void	updateAnimations();
};
#endif