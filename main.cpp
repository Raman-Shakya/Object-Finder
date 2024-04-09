#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "Block.h"
#include "World.h"
#include "Player.h"
#include "Object.h"

World world = World(5);
//Object obj = Object(1,4);
//Player player = Player();


void MyInit() {
	glClearColor(0.2, 0.2, 0.3, 1);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1,-0.1,0.1, 0.1, 20);
	glMatrixMode(GL_MODELVIEW); 
}


void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	world.player->positionCamera();
	
	world.render();
//	obj.render();
	
////	const char* texto = "texto";
////    glRasterPos2i( 0, 0 );
////    glColor3f( 0.0f, 0.0f, 1.0f );
//////    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char*)texto );
////	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'A');

	
	glutSwapBuffers();
}

void Key(unsigned char ch, int x, int y) {
	switch (ch) {
		case 'w': world.player->moveFront(); break;
		case 's': world.player->moveBack(); break;
		case 'a': world.player->moveLeft(); break;
		case 'd': world.player->moveRight(); break;
		case 'q': world.player->lookLeft(); break;
		case 'e': world.player->lookRight(); break;
	}
	world.correctPlayer();
//	player.showPos();
	glutPostRedisplay();
}

int main(int argC, char *argV[]) {
    srand(time(NULL));

	glutInit(&argC, argV);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 150);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Object Finder");
	MyInit();
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutMainLoop();
	return 0;
}
