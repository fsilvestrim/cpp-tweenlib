/*
 *  MainApp.h
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <string>
#include <iostream>

#include "Parser.h"

using namespace std;

class MainApp
{
public:
	MainApp();
	~MainApp();
	void		init(int argc, char ** argv);
	void		parseLine( string & );

private:
	Parser			parser;
};

