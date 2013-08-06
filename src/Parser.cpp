/*
 *  Parser.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream> 

#include "Parser.h"
#include "Easing.h"

void Parser::explodeLine ( string &line )
{
	char *temp;
	int cont = 0;
	char *l = (char*) line.data();
	
	temp = strtok(l, " ");
	
	while (temp != NULL)
	{
		words[cont++] = temp;
		temp = strtok(NULL, " ");
	}
	
	s.clear();
	s.append(words[1]);
}

void Parser::parse ( string &line )
{	
	int caseOfParse = 0;
	caseOfParse = line.substr(0, 6) == "create" ? 1 : caseOfParse;
	caseOfParse = line.substr(0, 6) == "camera" ? 2 : caseOfParse;
	caseOfParse = line.substr(0, 4) == "hide"	? 3 : caseOfParse;
	caseOfParse = line.substr(0, 4) == "show"	? 4 : caseOfParse;
	caseOfParse = line.substr(0, 6) == "lookat"	? 5 : caseOfParse;
	
	caseOfParse = line.substr(0, 7) == "objects"	? -1 : caseOfParse;
	caseOfParse = line.substr(0, 9) == "animation"	? -1 : caseOfParse;
	caseOfParse = line.substr(0, 1) == "#"			? -1 : caseOfParse;
	caseOfParse = line.substr(0, 1) == "\n"			? -1 : caseOfParse;
	caseOfParse = line.empty()						? -1 : caseOfParse;
	
	if(caseOfParse != -1)
	{
		explodeLine(line);
	}
		
	switch (caseOfParse) 
	{
		case -1:
			break;
			
		case 1: // CREATE
			{
				if (s == "camera")
				{
					obj = new Object(Object::CAMERA, "camera");
					
					obj->setPosition(atoi(words[3]), atoi(words[4]), atoi(words[5]));
					obj->setCameraLookAt(atoi(words[7]), atoi(words[8]), atoi(words[9]));
					obj->setCameraUp(atoi(words[11]), atoi(words[12]), atoi(words[13]));
					obj->setVisibility(0, true);
					
					TweenLib::getInstance()->addObject(obj);
				}
				else
				{
					if (s == "box" || s == "sphere" || s == "cylinder" || s == "cone")
					{
						int value = s == "box" ? Object::BOX : (s == "sphere" ? Object::SPHERE : (s == "cylinder" ? Object::CYLINDER : (s == "cone" ? Object::CONE : -1)));
						
						obj = new Object(value, words[2]);
						
						obj->setPosition(atoi(words[4]), atoi(words[5]), atoi(words[6]));
						obj->setRotate(atoi(words[8]), atoi(words[9]), atoi(words[10]), atoi(words[11]));
						obj->setScale(atoi(words[13]), atoi(words[14]), atoi(words[15]));
						obj->setColor(atoi(words[17]), atoi(words[18]), atoi(words[19]));
						obj->setVisibility(atoi(words[21]), true);
						
						TweenLib::getInstance()->addObject(obj);
					}
				}
			}
			break;

		case 3: // HIDE OBJECT
			{
				obj = TweenLib::getInstance()->objMap[words[1]];
				obj->setVisibility(atoi(words[3]), false);
			}
			break;
		
		case 4: // SHOW OBJECT
			{
				obj = TweenLib::getInstance()->objMap[words[1]];
				obj->setVisibility(atoi(words[3]), true);
			}
			break;
			
		default: // ANIMATION
			{
				string firstElement;
				firstElement.clear();
				firstElement.append(words[0]);
				
				if(firstElement.size() > 1) // não é linha em branco
				{
					
				int startFrame;
				int endFrame;
				int value	= -1;
				int sum		= 0;
				int ease	= Easing::LINEAR;
				map<int, float> endValuesAnimObj;
				map<int, float> endValuesAnimObjAux;
				
				if(caseOfParse == 2) // PURE CAMERA
				{
					obj		= TweenLib::getInstance()->objMap["camera"];
					value	= s == "translate" ? Animation::TRANSLATE : (s == "up" ? Animation::UP : -1);
				}
				else if (caseOfParse == 5) // LOOKAT
				{
					obj		= TweenLib::getInstance()->objMap["camera"];
					value	= Animation::LOOKAT;
				}
				else
				{
					cout << "\n ANIMATION test >> " << words[0];
					obj		= TweenLib::getInstance()->objMap[words[0]];
					value	= s == "translate" ? Animation::TRANSLATE : (s == "rotate" ? Animation::ROTATE : (s == "scale" ? Animation::SCALE : -1));
				}
				
				cout << "\n ANIMATION PARSE >> " << obj->getName();
				
				ease	= s == "bezier" ? Easing::BEZIER : (s == "catmull" ? Easing::CATMULL_ROM : ease);

				endValuesAnimObj[0] = atof(words[2]);
				endValuesAnimObj[1] = atof(words[3]);
				endValuesAnimObj[2] = atof(words[4]);
				
				if(s == "rotate") { endValuesAnimObj[3] = atof(words[5]); sum = 1;}
				if(ease !=  Easing::LINEAR)
				{
					endValuesAnimObjAux[0]		= atof(words[5]);
					endValuesAnimObjAux[1]		= atof(words[6]);
					endValuesAnimObjAux[2]		= atof(words[7]);
					endValuesAnimObjAux[100]	= atof(words[8]);
					endValuesAnimObjAux[101]	= atof(words[9]);
					endValuesAnimObjAux[102]	= atof(words[10]);
					sum = 6;
				}
				
				startFrame	= atoi(words[6 + sum]);
				endFrame	= (int) words.size() > (7 + sum) ? atoi(words[8 + sum]) : atoi(words[6 + sum]);
				anim		= new Animation(obj, value, endValuesAnimObj, startFrame, endFrame, ease);
				
				if(ease !=  Easing::LINEAR) { anim->setAuxValues(endValuesAnimObjAux); }
				
				TweenLib::getInstance()->addAnimation(anim);
				//*/
					
				}
			}
			break;
	}
}