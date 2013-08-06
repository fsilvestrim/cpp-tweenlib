/*
 *  Parser.h
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>
#include <string>
#include <map>

#include "TweenLib.h"

using namespace std;

class Parser 
{
public:
	void parse( string &line );
	
private:
	map<int, char*>		words;
	string				s;
	
	Object		*obj;
	Animation	*anim;
	
	void explodeLine ( string &line );
};