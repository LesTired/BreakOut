/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * level-data.h
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

#ifndef _LEVEL_DATA_H_
#define _LEVEL_DATA_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include <cairomm/context.h>

#include "math-vector2-d.h"
#include "brick-data.h"

class BrickData;
class GameData;

class LevelData
{
friend class GameData;
public:
	LevelData(double, double, int, int);
	LevelData(double, double, std::string);
	virtual ~LevelData();

	void draw(const Cairo::RefPtr <Cairo::Context>&);

protected:
	std::vector<std::vector<BrickData>> BrickField;
};

#endif // _LEVEL_DATA_H_

