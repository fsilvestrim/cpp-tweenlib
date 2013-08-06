/*
 *  MainApp.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "MainApp.h"
#include "TweenLib.h"
#include "Easing.h"

MainApp::MainApp ()
{
	cout << "\nBUILD MAINAPP";
}

MainApp::~MainApp ()
{
	cout << "\nDESTROY MAINAPP";
}

void MainApp::init (int argc, char ** argv)
{
	/*
	Object *obj1 = new Object(Object::BOX, "box1");
	obj1->setPosition(0, 0, 0);
	obj1->setColor(255, 255, 255);
	obj1->setVisibility(15, true);
	//obj1->setVisibility(150, false);
	//obj1->setVisibility(170, true);
	TweenLib::getInstance()->addObject(obj1);
	
	map<int, float> endValues;
	endValues[0] = 2;
	endValues[1] = 1;
	endValues[2] = 1;
	Animation *anims1 = new Animation(obj1, Animation::SCALE, endValues, 30, 100);
	TweenLib::getInstance()->addAnimation(anims1);
	
	map<int, float> endValuess2;
	endValuess2[0] = 10;
	endValuess2[1] = 0;
	endValuess2[2] = 0;
	Animation *anims2 = new Animation(obj1, Animation::TRANSLATE, endValuess2, 100, 150);
	TweenLib::getInstance()->addAnimation(anims2);
	
	//camera
	
	Object *objCam = new Object(Object::CAMERA, "cam");
	objCam->setPosition(0, 0, 10);
	objCam->setCameraLookAt(0, 0, 0);
	objCam->setCameraUp(0, 1, 0);
	TweenLib::getInstance()->addObject(objCam);
	
	map<int, float> endValues2;
	endValues2[0] = 0;
	endValues2[1] = 0;
	endValues2[2] = -20;
	map<int, float> auxValues;
	auxValues[0] = 30;
	auxValues[1] = 0;
	auxValues[2] = 20;
	auxValues[100] = 30;
	auxValues[101] = 0;
	auxValues[102] = -20;
	
	Animation *anim2 = new Animation(2, objCam, Animation::TRANSLATE, endValues2, 30, 100, Easing::BEZIER);
	anim2->setAuxValues(auxValues);
	TweenLib::getInstance()->addAnimation(anim2);
	 //*/
}

void MainApp::parseLine( string &data )
{	
	parser.parse(data);
}




