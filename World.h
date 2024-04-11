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
	Object *obj;
	int seed;
	
	void resetLevel() {
		int i, j;
		for (i=0; i<currentLevel; i++) {
			for (j=0; j<currentLevel; j++) {
				tempGrid[i][j] = '#';
				delete mainGrid[i][j];
				mainGrid[i][j] = NULL;
			}
		}
		delete player;
		player = new Player();
		drawLevel();
	}
	void generateLevel(char temp[MAX_LEVEL][MAX_LEVEL], int i, int j) {
		if (i==currentLevel-2 && j==currentLevel-2) {
			return;
		}
	    
		std::vector< std::pair<int, int> > orientation;
		orientation.push_back({0, -1});
		orientation.push_back({0,  1});
		orientation.push_back({-1, 0});
		orientation.push_back({1,  0});
		std::random_shuffle(orientation.begin(), orientation.end());
		rand();
		
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
		// srand(currentLevel);
		int i,j;
		temp[1][1] = ' ';
		// empty
		for (i=0; i<currentLevel; i++)
			for (j=0; j<currentLevel; j++)
				temp[i][j]='#';
		generateLevel(temp, 1, 1);
//		for (i=0; i<currentLevel; i++){
//			for (j=0; j<currentLevel; j++)
//				std::cout << temp[i][j] << " ";
//			std::cout << std::endl;
//		}
				
				
		for (i=0; i<currentLevel; i++) {
			for (j=0; j<currentLevel; j++) {
				tempGrid[i][j] = temp[i][j];
				if (tempGrid[i][j]=='#')
					mainGrid[i][j] = new Block(i, j);
				else
					mainGrid[i][j] = NULL;
			}
		}
		placeObject();
	}
	
	void placeObject() {
		int i = rand() % currentLevel, j = rand() % currentLevel;
		if (tempGrid[i][j]=='#') return placeObject();
		tempGrid[i][j] = 'o';
		obj = new Object(i, j);
	}
	
public:
	int currentLevel;	// size of the current nxn level
	Player *player;
	
	World(int level=3) {
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
		delete obj;
		delete player;
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
		obj->render();
	}
	
	void correctPlayer() {
		int posx = round(player->pos[0]/WIDTH), posz = round(player->pos[2]/WIDTH);
		
		if (tempGrid[posx][posz]=='o') {
			std::cout << "block found\n";
			nextLevel();
		}

		int upBlock = tempGrid[posx-1][posz] == '#',
			downBlock = tempGrid[posx+1][posz] == '#',
			leftBlock = tempGrid[posx][posz+1] == '#',
			rightBlock = tempGrid[posx][posz-1] == '#';
		
		if (upBlock) {
			if (player->pos[0] < (posx-0.3)*WIDTH) player->pos[0] = (posx-0.3)*WIDTH;
		}
		if (downBlock) {
			if (player->pos[0] > (posx+0.3)*WIDTH) player->pos[0] = (posx+0.3)*WIDTH;
		}
		if (leftBlock) {
			if (player->pos[2] > (posz+0.3)*WIDTH) player->pos[2] = (posz+0.3)*WIDTH;
		}
		if (rightBlock) {
			if (player->pos[2] < (posz-0.3)*WIDTH) player->pos[2] = (posz-0.3)*WIDTH;
		}
	}
	
	void nextLevel() {
		currentLevel += 2;
		resetLevel();
	}
};
