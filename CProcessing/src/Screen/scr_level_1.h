#pragma once

GridUnit level[GRID_WIDTH][GRID_HEIGHT];

void Level1Init(void);
void LevelDraw(Player* player);
void Level1Update(Player* player);
void Level1Exit(void);