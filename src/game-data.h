/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game-data.h
 * Copyright (C) 2017 Michael Lehner <010.wintermute@gmail.com>
 *
 * BreakOut is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BreakOut is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <string>

#include <cairomm/context.h>

#include "math-vector2-d.h"
#include "dir-reader.h"
#include "env-vectorize.h"
#include "ball-data.h"
#include "paddle-data.h"
#include "brick-data.h"
#include "level-data.h"
#include "collision-model-data.h"

class Graphics;
class MainWindow;

class GameData
{
friend class Graphics;
friend class MainWindow;
public:
	GameData(int, int);
	virtual ~GameData();

protected:
	void propagate_time();

	int Window_width;
	int Window_height;

	BallData Ball;
	PaddleData Paddle;

	std::vector<std::string> level_files;
	LevelData Level;

	int lives;

	bool Game_over;
	bool Game_paused;
};

#endif // _GAME_DATA_H_
