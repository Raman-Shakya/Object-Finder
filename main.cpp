#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "Game.h"

Game *game;

void Draw() {
	game->draw();
}

void Key(unsigned char ch, int x, int y) {
	game->Key(ch, x, y);
}

int main(int argC, char *argV[]) {
    srand(time(NULL));

	glutInit(&argC, argV);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(100, 150);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Object Finder");

	game = new Game();
	
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutMainLoop();
	return 0;
}
