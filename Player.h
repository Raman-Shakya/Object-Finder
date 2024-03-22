#pragma once
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

class Player {
	GLfloat pos[3];
	GLfloat dir[4];
	double delta, cosA, sinA;
	
	void showData() {
		std::cout << "position: " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
		std::cout << "direction:" << dir[0] << " " << dir[1] << " " << dir[2] << std::endl;

	}
	
public:
	Player() {
		delta = 0.1;
		pos[0] = 0; pos[1] = 0; pos[2] = 3;
		dir[0] = 0; dir[1] = 0; dir[2] = -0.1;
		showData();
		sinA = sin(delta);
		cosA = cos(delta);
		std::cout << sinA << " " << cosA << std::endl;
	}
	~Player() {
	}
	
	void lookLeft() {
		GLfloat nextX = dir[0] * cosA + dir[2] * sinA;
		GLfloat nextZ = -dir[0] * sinA + dir[2] * cosA;
		dir[0] = nextX;
		dir[2] = nextZ;
		showData();
	}
	void lookRight() {
		GLfloat nextX = dir[0] * cosA - dir[2] * sinA;
		GLfloat nextZ = dir[0] * sinA + dir[2] * cosA;
		dir[0] = nextX;
		dir[2] = nextZ;
		showData();
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
		pos[2] += dir[0];
	}
	void moveRight() {
		pos[0] -= dir[2];
		pos[2] -= dir[0];
	}
	void positionCamera() {
		gluLookAt(pos[0], pos[1], pos[2],
		  		  pos[0]+dir[0], pos[1]+dir[1], pos[2]+dir[2],
		  	      0, 1, 0
		);
	}
};
