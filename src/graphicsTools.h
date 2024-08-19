#pragma once

#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>


void stringDisplay(std::string str, void* font, float x, float y) {
    glColor3f( 0.8f, 0.3f, 0.0f );
    for (int i=0; i<str.length(); i++) {
    	glRasterPos2i( x, y );
    	unsigned char ch = str[i];
    	glutBitmapCharacter(font, ch);
    	x += glutBitmapWidth(font, ch);
	}
}

void drawRect(float x, float y, float w, float h) {
	glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x, y+h);
    glEnd();
}
