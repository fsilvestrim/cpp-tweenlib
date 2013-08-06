/*
 *  main.cpp
 *  AnimationProject
 *
 *  Created by Filipe Silvestrim on 4/18/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream> 
#include <string>
#include <map>
#include <GLUT/GLUT.h>


#include "Object.h"
#include "TweenLib.h"
#include "MainApp.h";

//namespace
using namespace std;

//main attributes
MainApp application;

/**
 * GLUT
 */
const int        windowHeight   = 500;
const int        windowWidth    = 500;
const int        windowX        = 0;
const int        windowY        = 0;
const char*        windowName   = "Filipe Silvestrim - Animation Project";
const int        displayMode	= GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_ACCUM;

static float ratio;
static float cx=0.0f,cy=0.0f,cz=5.0f;
static float clx=0.0f,cly=0.0f,clz=0.0f;
static float cux=0.0f,cuy=1.0f,cuz=0.0f;

int        specialKey            = 0;
int        font                = (int) GLUT_BITMAP_8_BY_13;
int        fontBitmapHeight    = 13;

int			FPS_WANTED			= 21;
int			fpsFrame            = 0;
int			fpsTime             = 0;
int			fpsTimebase         = 0;
int			newTime, lastTime;

bool		appRunning;

char txtCurrentFPS[30];
char txtCurrentFrame[50];
char txtInputFileName[50];
int countInput = 0;


GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

/**
 * TEXT AND 2D PROJECTION
 */
void setOrthographicProjection()
{
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);
    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();
    // reset matrix
    glLoadIdentity();
    // set a 2D orthographic projection
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    // invert the y axis, down is positive
    glScalef(1, -1, 1);
    // mover the origin from the bottom left corner
    // to the upper left corner
    glTranslatef(0, -windowHeight, 0);
    glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *string)
{
    char *c;
    int x1 = x;
    for (c = string; *c != '\0'; c++)
    {
        glRasterPos2f(x1, y);
        glutBitmapCharacter(font, *c);
        x1 = x1 + glutBitmapWidth(font, *c) + spacing;
    }
}

void renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font, char *string)
{
    char *c;
    int i;
    for (c = string, i = 0; *c != '\0'; i++, c++)
    {
        glRasterPos2f(x, y + bitmapHeight * i);
        glutBitmapCharacter(font, *c);
    }
}

void drawTexts()
{	
	renderBitmapString(0, 490, (void *) font, "Press ESC to exit.");
	renderBitmapString(180, 490, (void *) font, "Press UP/DOWN to change (in 10) the FPS.");
	
	if(!appRunning)
	{
		renderBitmapString(100, 250, (void *) font, "Insert the name of the script file: ");
		renderBitmapString(100, 280, (void *) font, txtInputFileName);
	}
	else
	{
		renderBitmapString(300, 30, (void *) font, txtCurrentFPS);
		renderBitmapString(300, 10, (void *) font, txtCurrentFrame);
		renderBitmapString(0, 10, (void *) font, "Animation Project by Filipe S.");
	}
}

/**
 * OBJECTS
 * UPDATE AND DRAW
 */
void drawObject ( Object *obj )
{	
	if(obj->isVisibleAt(TweenLib::getInstance()->currentFrame) && obj->getType() != Object::CAMERA)
	{
		glPushMatrix();
		
		glColor3fv(obj->getColor());
		glRotatef(obj->getRotate()[3], obj->getRotate()[0], obj->getRotate()[1], obj->getRotate()[2]);
		glTranslatef(obj->getPosition()[0], obj->getPosition()[1], obj->getPosition()[2]);
		glScalef(obj->getScale()[0], obj->getScale()[1], obj->getScale()[2]);
		
		switch (obj->getType()) 
		{
			case Object::SPHERE:
					glutSolidSphere(obj->getSize()[0], 20, 20);
				break;
			case Object::BOX:
					glutSolidCube(obj->getSize()[0]);
				break;
			case Object::CONE:
					glutSolidCone(obj->getSize()[0], obj->getSize()[1], 20, 20);
				break;
			case Object::CYLINDER:
					gluCylinder(gluNewQuadric(), obj->getSize()[0], obj->getSize()[1], obj->getSize()[2], 20, 20);
				break;
		}
		
		glPopMatrix();
	}
	else if (obj->getType() == Object::CAMERA)
	{
		cx = obj->getPosition()[0];
		cy = obj->getPosition()[1];
		cz = obj->getPosition()[2];
		clx = obj->getCameraLookAt()[0];
		cly = obj->getCameraLookAt()[1];
		clz = obj->getCameraLookAt()[2];
		cux = obj->getCameraUp()[0];
		cuy = obj->getCameraUp()[1];
		cuz = obj->getCameraUp()[2];
		
		glLoadIdentity();
		gluLookAt(cx, cy, cz, clx, cly, clz, cux, cuy, cuz);
	}
}

void update ()
{
	TweenLib::getInstance()->updateAnimations();
}

void render(void)
{	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);		// Enable Lighting
	
    //draw anything
    for ( TweenLib::getInstance()->itObj = TweenLib::getInstance()->objMap.begin(); TweenLib::getInstance()->itObj != TweenLib::getInstance()->objMap.end(); TweenLib::getInstance()->itObj++ )
        drawObject((*TweenLib::getInstance()->itObj).second);
    
	glDisable(GL_LIGHTING);		// Disable Lighting
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 1.0f);
    setOrthographicProjection();
    glLoadIdentity();
    drawTexts();
    resetPerspectiveProjection();
    glPopMatrix();
	
    glutSwapBuffers();
}

/**
 * GLUT OTHERS CALLBACKS
 */
void reshape(int w, int h)
{
	 // Prevent a divide by zero, when window is too short
	 // (you cant make a window of zero width).
	 if(h == 0)	 h = 1;
	 
	 ratio = 1.0f * w / h;
	
	 // Reset the coordinate system before modifying
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 
	 // Set the viewport to be the entire window
	 glViewport(0, 0, w, h);
	 
	 // Set the clipping volume
	 gluPerspective(45,ratio,1,1000);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 gluLookAt(cx, cy, cz, clx, cly, clz, cux, cuy, cuz);
}

void keyDown(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }
}

void keyUp(unsigned char key, int x, int y)
{
    if (key == 27) //esc
    {
        exit(0);
    }
	else if (key == 13) //return
	{
		/*
		 * Initializing File Read
		 */
		string line;
		const char *ptStr = 0;
		ptStr = txtInputFileName;
		
		ifstream scriptFile (ptStr); 
		
		if (scriptFile.is_open()) 
		{			
			while (! scriptFile.eof() ) 
			{ 
				getline (scriptFile, line);
				
				if(!line.empty())
				{
					application.parseLine( line );
				}
			}
			
			scriptFile.close();
			
			TweenLib::getInstance()->currentFrame = 0;
			appRunning = true;
		}
		else
		{
			cout << "\n Ocorreu um erro ao tentar abrir o arquivo!";
		}
	}
	else if (key == 8) //backspace
	{
		if(countInput > 0)
		{
			const char *sp = " ";
			txtInputFileName[--countInput] = *sp;
		}
	}
	else
	{
		txtInputFileName[countInput++] = key;
	}
}

void pressKey(int key, int x, int y)
{
	if(key == GLUT_KEY_DOWN && FPS_WANTED > 1)
	{
		FPS_WANTED -= 10;
	}
	else if(key == GLUT_KEY_UP && FPS_WANTED < 1000)
	{
		FPS_WANTED += 10;
	}
}

void releaseKey(int key, int x, int y)
{
    
}

void processMouse(int button, int state, int x, int y)
{
    specialKey = glutGetModifiers();
    
    // if both a mouse button, and the ALT key, are pressed  then
    if ((state == GLUT_DOWN) && (specialKey == GLUT_ACTIVE_ALT))
    {
        // set the color to pure red for the left button
        if (button == GLUT_LEFT_BUTTON)
        {
            
        }
        // set the color to pure green for the middle button
        else if (button == GLUT_MIDDLE_BUTTON)
        {
            
        }
        // set the color to pure blue for the right button
        else
        {
            
        }
    }
}

void processMouseActiveMotion(int x, int y)
{
}

void processMousePassiveMotion(int x, int y)
{
}

void processMouseEntry(int state)
{
}

/**
 * MAIN LOOP
 */
void mainLoop()
{
	//fixed timestep
	while (newTime < lastTime + (1000/FPS_WANTED))
	{
		newTime = glutGet(GLUT_ELAPSED_TIME);
		update();
	}
	
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	
	/*
	 * MAIN RENDER
	 */
    render();
	
	//fps calc
	fpsFrame++;
    fpsTime = glutGet(GLUT_ELAPSED_TIME);
    if (fpsTime - fpsTimebase > 1000)
    {
        sprintf(txtCurrentFPS, "FPS:%4.2f", fpsFrame * 1000.0 / (fpsTime - fpsTimebase));
        fpsTimebase = fpsTime;
        fpsFrame = 0;
    }
	
	//frame count
	TweenLib::getInstance()->currentFrame++;
	sprintf(txtCurrentFrame, "CURRENT FRAME :: %i", TweenLib::getInstance()->currentFrame);
}

/**
 * INIT
 */
void initialize()
{    
	glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// Black Background
	glClearDepth(1.0f);							// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			// Position The Light
	glEnable(GL_LIGHT1);							// Enable Light One
    
    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

/**
 * INIT GLUT
 */
int init(int argc, char** argv)
{    
    glutInit(&argc, argv);
    glutInitDisplayMode(displayMode);
    
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow(windowName);
    //glutFullScreen();
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(mainLoop);
    glutIdleFunc(mainLoop);
    
    //adding keyboard functionallity
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    
	//overlap
	glEnable(GL_DEPTH_TEST);
	
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    
    //adding here the mouse processing callbacks
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseActiveMotion);
    glutPassiveMotionFunc(processMousePassiveMotion);
    glutEntryFunc(processMouseEntry);
    
	initialize();
	glutMainLoop();
	
    return EXIT_SUCCESS;
}

/**
 * MAIN
 */
int main (int argc, char ** argv) 
{
	application.init(argc, argv);
	init(argc, argv);
}