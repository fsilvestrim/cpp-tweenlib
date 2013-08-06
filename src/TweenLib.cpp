/*
 *  TweenLib.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/18/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "TweenLib.h"
#include <iostream>

TweenLib *TweenLib::instance = 0;

TweenLib::TweenLib ()
{
	currentFrame = 0;
}

TweenLib::~TweenLib()
{
	
}

void TweenLib::addObject(Object *obj)
{
	objMap[obj->getName()] = obj;
}

void TweenLib::addAnimation(Animation *anim)
{
	animMap[anim->getId()] = anim;
}

void TweenLib::updateAnimations()
{
	Animation *anim;
	
	for ( itAnim = animMap.begin() ; itAnim != animMap.end(); itAnim++ )
	{
		anim = (*itAnim).second;
		
		if(currentFrame >= anim->getStartFrame() && currentFrame <= anim->getEndFrame())
		{
			anim->run(currentFrame);
		}
	}
}

TweenLib *TweenLib::getInstance()
{
	if(TweenLib::instance == 0){
		TweenLib::instance = new TweenLib;
	}
	
	return TweenLib::instance;
}
