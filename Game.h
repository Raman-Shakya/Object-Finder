#pragma once
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "World.h"
#include "graphicsTools.h"

struct State {
	int MAIN_MENU = 0;
	int GAME = 1;
	int PAUSE_SCREEN = 2;
	int CONTROL_SCREEN = 3;
} states;

class Game {
	World *world;
	int state;
	
	void set2DMode() {
		glClearColor(0.2, 0.2, 0.3, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-WIN_WIDTH/2, WIN_WIDTH/2, -WIN_HEIGHT/2, WIN_HEIGHT/2);
	}
	void set3DMode() {
		glClearColor(0.2, 0.2, 0.3, 1);
		glEnable(GL_DEPTH_TEST);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.1, 0.1,-((double) WIN_HEIGHT / WIN_WIDTH) * 0.1f, ((double) WIN_HEIGHT / WIN_WIDTH) * 0.1f, 0.1, 20);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	// drawing function declarations
	void drawMainMenu();
	void drawPauseScreen();
	void drawControlScreen();

	void pauseGame() {
		state = states.PAUSE_SCREEN;
		draw();
	}
public:
	// initializer
	Game() {
		set3DMode();
		world = new World(5);	// starting level 5
		state = states.MAIN_MENU; // initial screen at main menu
	}
	// memory management
	~Game() {
		delete world;
	}
	
	
	// keyboard inputs
	void Key(unsigned char ch, int x, int y) {
		if (state == states.MAIN_MENU || state == states.PAUSE_SCREEN || state == states.CONTROL_SCREEN) {
			switch (ch) {
				case 'p': state = states.GAME; break;
				case 'i': state = states.CONTROL_SCREEN; break;
				case 'e':
					glutDestroyWindow(glutGetWindow());
					delete world;
					break;
				default: break;
			}
			draw();
		}
		else if (state == states.GAME) {
			switch (ch) {
				case 'w': world->player->moveFront(); break;
				case 's': world->player->moveBack(); break;
				case 'a': world->player->moveLeft(); break;
				case 'd': world->player->moveRight(); break;
				case 'q': world->player->lookLeft(); break;
				case 'e': world->player->lookRight(); break;
				case 'p': pauseGame(); break;
			}
			world->correctPlayer();
			glutPostRedisplay();
		}
	}
	
	// draw function
	void draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		if (state == states.MAIN_MENU) {
			set2DMode();
			drawMainMenu();	
		}
		else if (state == states.GAME) {
			set3DMode();
			world->player->positionCamera();
			world->render();
		}
		else if (state == states.PAUSE_SCREEN) {
			set2DMode();
			drawPauseScreen();
		}
		else if (state == states.CONTROL_SCREEN) {
			set2DMode();
			drawControlScreen();
		}
		glutSwapBuffers();
	}
};




void Game::drawMainMenu() {
	stringDisplay("OBJECT FINDER", FONT_B, -75, 100);
	stringDisplay("play (p)", FONT_M, -30, 50);
	stringDisplay("controls (i)", FONT_M, -30, 20);
	stringDisplay("exit (e)", FONT_M, -30, -10);
	drawRect(-100, 100, 20, 30);
}
void Game::drawPauseScreen() {
	stringDisplay("PAUSED", FONT_B, -75, 100);
	std::string currentLevel = "level : ";
	char level[4];
	int level_i = (world->currentLevel - 3) / 2;
	itoa(level_i, level, 10);
	currentLevel += std::string(level);
	stringDisplay(currentLevel, FONT_B, -30, 50);
	
	stringDisplay("play (p)", FONT_M, -30, 10);
	stringDisplay("controls (i)", FONT_M, -30, -10);
	stringDisplay("exit (e)", FONT_M, -30, -30);
	drawRect(-100, 100, 20, 30);
}

void Game::drawControlScreen() {
	stringDisplay("CONTROLS", FONT_B, -75, 100);
	stringDisplay("move up   :  (w)", FONT_M, -40, 50);
	stringDisplay("move down :  (s)", FONT_M, -40, 30);
	stringDisplay("move left :  (a)", FONT_M, -40, 10);
	stringDisplay("move right:  (d)", FONT_M, -40, -10);
	
	stringDisplay("look left :  (q)", FONT_M, -40, -40);
	stringDisplay("look right:  (e)", FONT_M, -40, -60);
	
	stringDisplay("to continue press p", FONT_M, -60, -120);
	stringDisplay("to exit press e"    , FONT_M, -60, -140);
	
	drawRect(-100, 100, 20, 30);
}









