#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h> 

#include "constant.h"
#include "Player.h"
#include "Block.h"
#include "Object.h"

class World {
	char tempGrid[MAX_LEVEL][MAX_LEVEL];	// map in character grid
	Block *mainGrid[MAX_LEVEL][MAX_LEVEL];  // main map to render
	int currentLevel;	// size of the current nxn level
	int seed = 1;
	
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
	void generateLevel(char temp[MAX_LEVEL][MAX_LEVEL], int i, int j) {
		if (i==currentLevel-2 && j==currentLevel-2) {
			return;
		}
	    srand(seed);
	    
		std::vector< std::pair<int, int> > orientation;
		orientation.push_back({0, -1});
		orientation.push_back({0,  1});
		orientation.push_back({-1, 0});
		orientation.push_back({1,  0});
		std::random_shuffle(orientation.begin(), orientation.end());
		seed = rand();
		
		// main part
		int iter;
		for (iter=0; iter<orientation.size(); iter++) {
			int destI = i+2*orientation[iter].first, destJ = j+2*orientation[iter].second;
			if (destI > 0 && destJ > 0 && destI < currentLevel-1 && destJ < currentLevel-1 && temp[destI][destJ]=='#') {
				temp[i+orientation[iter].first][j+orientation[iter].second] = ' ';
				temp[destI][destJ] = ' ';
				generateLevel(temp, destI, destJ);
			}
		}
	}
	void drawLevel() {
		char temp[MAX_LEVEL][MAX_LEVEL];
		int i,j;
		temp[1][1] = ' ';
		// empty
		for (i=0; i<currentLevel; i++)
			for (j=0; j<currentLevel; j++)
				temp[i][j]='#';
		generateLevel(temp, 1, 1);
		for (i=0; i<currentLevel; i++){
			for (j=0; j<currentLevel; j++)
				std::cout << temp[i][j] << " ";
			std::cout << std::endl;
		}
				
				
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
