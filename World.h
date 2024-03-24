#pragma once

#include <iostream>
#include "constant.h"
#include "Player.h"
#include "Block.h"
#include "Object.h"

class World {
	char tempGrid[MAX_LEVEL][MAX_LEVEL];	// map in character grid
	Block *mainGrid[MAX_LEVEL][MAX_LEVEL];  // main map to render
	int currentLevel;	// size of the current nxn level
	
	void resetLevel() {
		int i, j;
		for (i=0; i<currentLevel; i++) {
			for (j=0; j<currentLevel; j++) {
				tempGrid[i][j] = '#';
				mainGrid[i][j] = NULL;
			}
		}
		drawLevel();
	}
	void drawLevel() {
		char temp[currentLevel+1][currentLevel+1] = {
			"#########",
			"# #     #",
			"# # ### #",
			"#   #   #",
			"##### ###",
			"#   #   #",
			"# # # ###",
			"# #     #",
			"#########",
		};
		int i,j;
		for (i=0; i<currentLevel; i++) {
			for (j=0; j<currentLevel; j++) {
				tempGrid[i][j] = temp[i][j];
				if (tempGrid[i][j]=='#')
					mainGrid[i][j] = new Block(i, j);
				else
					mainGrid[i][j] = NULL;
			}
		}
	}
public:
	World(int level=10) {
		currentLevel = level;	
		resetLevel();
	}
	~World() {
		int i, j;
		for (i=0; i<currentLevel; i++) {
			for (j=0; j<currentLevel; j++) {
				if (mainGrid[i][j]!=NULL)
					delete mainGrid[i][j];
			}
		}
	}
	void render() {
		int i, j;
		for (i=0; i<currentLevel; i++) {
			for (j=0; j<currentLevel; j++) {
				if (mainGrid[i][j]!=NULL) {
					mainGrid[i][j]->render();
				}
			}
		}
	}
};
