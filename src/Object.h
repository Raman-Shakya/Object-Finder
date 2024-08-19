#pragma once

#include <iostream>
#include "block.h"


class Object: public Block {
public:
	Object(float i, float j) : Block(i, j) {
		this->width = 0.2*WIDTH;
		calculateVertices();
	}
	
	void render() {
		glColor3f(0.5, 0.5, 0.5); Square(vertices[0], vertices[1], vertices[2], vertices[3]); // front
		glColor3f(0.5, 0.5, 0.5); Square(vertices[4], vertices[5], vertices[6], vertices[7]); // back
		glColor3f(1, 0, 1); Square(vertices[0], vertices[1], vertices[5], vertices[4]); // top
		glColor3f(1, 0, 1); Square(vertices[3], vertices[2], vertices[6], vertices[7]); // bottom
		glColor3f(0.7, 0.7, 0.7); Square(vertices[0], vertices[3], vertices[7], vertices[4]); // left
		glColor3f(0.7, 0.7, 0.7); Square(vertices[1], vertices[5], vertices[6], vertices[2]); // right
	}
};
