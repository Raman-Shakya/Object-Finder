#pragma once
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

class World;
class Player {
	friend class World;
	
	GLfloat pos[3];
	GLfloat dir[4];
	double delta, cosA, sinA;
	
public:
	Player() {
		delta = 0.1;
		pos[0] = WIDTH; pos[1] = 0; pos[2] = WIDTH;
		dir[0] = 0.05; dir[1] = 0; dir[2] = 0.05;
		sinA = sin(delta);
		cosA = cos(delta);
	}
	~Player() {
	}
	void showPos() {
		std::cout << pos[0] << " " << pos[2] << std::endl;
	}
	void lookLeft() {
		GLfloat nextX = dir[0] * cosA + dir[2] * sinA;
		GLfloat nextZ = -dir[0] * sinA + dir[2] * cosA;
		dir[0] = nextX;
		dir[2] = nextZ;
	}
	void lookRight() {
		GLfloat nextX = dir[0] * cosA - dir[2] * sinA;
		GLfloat nextZ = dir[0] * sinA + dir[2] * cosA;
		dir[0] = nextX;
		dir[2] = nextZ;
	}
	void moveFront() {
		pos[0] += dir[0];
		pos[2] += dir[2];
	}
	void moveBack() {
		pos[0] -= dir[0];
		pos[2] -= dir[2];
	}
	
	void moveLeft() {
		pos[0] += dir[2];
		pos[2] -= dir[0];
	}
	void moveRight() {
		pos[0] -= dir[2];
		pos[2] += dir[0];
	}
	void positionCamera() {
		gluLookAt(pos[0], pos[1], pos[2],
		  		  pos[0]+dir[0], pos[1]+dir[1], pos[2]+dir[2],
		  	      0, 1, 0
		);
	}
};
