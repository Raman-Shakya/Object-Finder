#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "Block.h"
#include "World.h"
#include "Player.h"
#include "Object.h"

World world = World(10);
Object obj = Object(1,4);
Player player = Player();


void MyInit() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1,-0.1,0.1, 0.1, 10);
	glMatrixMode(GL_MODELVIEW); 
}


void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	player.positionCamera();
	
	world.render();
	obj.render();
	
	glutSwapBuffers();
}

void Key(unsigned char ch, int x, int y) {
	switch (ch) {
		case 'w': player.moveFront(); break;
		case 's': player.moveBack(); break;
		case 'a': player.moveLeft(); break;
		case 'd': player.moveRight(); break;
		case 'q': player.lookLeft(); break;
		case 'e': player.lookRight(); break;
	}
	world.correctPlayer(player);
//	player.showPos();
	glutPostRedisplay();
}

int main(int argC, char *argV[]) {
	glutInit(&argC, argV);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 150);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Object Finder");
	MyInit();
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutMainLoop();
	return 0;
}
