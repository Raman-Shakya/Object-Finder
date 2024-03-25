#pragma once

#include <iostream>
#include <math.h>
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
	void pushFromBlock(Player &pl, int x, int z) {
		std::cout << "before: " << pl.pos[0] << " " << pl.pos[2] << std::endl;
		// player should not be within x-WIDTH/2 to x+width/2
		if (pl.pos[0] < x*WIDTH && pl.pos[0]>(x-0.5)*WIDTH) pl.pos[0] = (x-0.6)*WIDTH;
		if (pl.pos[0] > x*WIDTH && pl.pos[0]>(x+0.5)*WIDTH) pl.pos[0] = (x+0.6)*WIDTH;
		// player should not be within z-WIDTH/2 to z+width/2
		if (pl.pos[2] < z*WIDTH && pl.pos[2]>(z-0.5)*WIDTH) pl.pos[2] = (z-0.6)*WIDTH;
		if (pl.pos[2] > z*WIDTH && pl.pos[2]>(z+0.5)*WIDTH) pl.pos[2] = (z+0.6)*WIDTH;
		std::cout << "after: " << pl.pos[0] << " " << pl.pos[2] << std::endl;
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
	
	void correctPlayer(Player &pl) {
		int posx = round(pl.pos[0]/WIDTH), posz = round(pl.pos[2]/WIDTH);

		int upBlock = tempGrid[posx-1][posz] == '#',
			downBlock = tempGrid[posx+1][posz] == '#',
			leftBlock = tempGrid[posx][posz+1] == '#',
			rightBlock = tempGrid[posx][posz-1] == '#';
		
		if (upBlock) {
			if (pl.pos[0] < (posx-0.3)*WIDTH) pl.pos[0] = (posx-0.3)*WIDTH;
		}
		if (downBlock) {
			if (pl.pos[0] > (posx+0.3)*WIDTH) pl.pos[0] = (posx+0.3)*WIDTH;
		}
		if (leftBlock) {
			if (pl.pos[2] > (posz+0.3)*WIDTH) pl.pos[2] = (posz+0.3)*WIDTH;
		}
		if (rightBlock) {
			if (pl.pos[2] < (posz-0.3)*WIDTH) pl.pos[2] = (posz-0.3)*WIDTH;
		}
	}
};
