#pragma once

#include <GL/glu.h>
#include <GL/glut.h>
#include "constant.h"
#include <iostream>

class Block {
	float width, x, y;
	GLfloat vertices[8][3];
	
	void Square(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
		glBegin(GL_POLYGON);
			glVertex3fv(A);
			glVertex3fv(B);
			glVertex3fv(C);
			glVertex3fv(D);
		glEnd();
	}
	
	void calculateVertices() {
		vertices[0][0] = x*WIDTH-0.5f*width; vertices[0][1] = y*WIDTH-0.5f*width; vertices[0][2] = (0.5f)*WIDTH;
		vertices[1][0] = x*WIDTH+0.5f*width; vertices[1][1] = y*WIDTH-0.5f*width; vertices[1][2] = (0.5f)*WIDTH;
		vertices[2][0] = x*WIDTH+0.5f*width; vertices[2][1] = y*WIDTH+0.5f*width; vertices[2][2] = (0.5f)*WIDTH;
		vertices[3][0] = x*WIDTH-0.5f*width; vertices[3][1] = y*WIDTH+0.5f*width; vertices[3][2] = (0.5f)*WIDTH;
		
		vertices[4][0] = x*WIDTH-0.5f*width; vertices[4][1] = y*WIDTH-0.5f*width; vertices[4][2] = (-0.5f)*WIDTH;
		vertices[5][0] = x*WIDTH+0.5f*width; vertices[5][1] = y*WIDTH-0.5f*width; vertices[5][2] = (-0.5f)*WIDTH;
		vertices[6][0] = x*WIDTH+0.5f*width; vertices[6][1] = y*WIDTH+0.5f*width; vertices[6][2] = (-0.5f)*WIDTH;
		vertices[7][0] = x*WIDTH-0.5f*width; vertices[7][1] = y*WIDTH+0.5f*width; vertices[7][2] = (-0.5f)*WIDTH;
	}
public:
	Block(float i, float j, float w) {
		x = i;
		y = j;
		width = w;
		calculateVertices();
	}
	~Block() {
		
	}
	
	void render() {
		glColor3f(1, 0, 0); Square(vertices[0], vertices[1], vertices[2], vertices[3]); // front
		glColor3f(1, 1, 0); Square(vertices[4], vertices[5], vertices[6], vertices[7]); // back
		glColor3f(1, 0, 1); Square(vertices[0], vertices[1], vertices[5], vertices[4]); // top
		glColor3f(1, 1, 1); Square(vertices[3], vertices[2], vertices[6], vertices[7]); // bottom
		glColor3f(0, 0, 1); Square(vertices[0], vertices[3], vertices[7], vertices[4]); // left
		glColor3f(0, 1, 0); Square(vertices[1], vertices[5], vertices[6], vertices[2]); // right
	}
	
	
};
