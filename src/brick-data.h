/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * brick-data.h
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

#ifndef _BRICK_DATA_H_
#define _BRICK_DATA_H_

#include <vector>
#include <cmath>
#include <iostream>

#include <cairomm/context.h>

#include "math-vector2-d.h"

class BallData;
class LevelData;
class GameData;
class CollisionModelData;
enum bricktype {NORMAL, SOLID, EMPTY};

class BrickData
{
friend class GameData;
friend class LevelData;
friend class CollisionModelData;
public:
	BrickData(double, double, double, double);
	BrickData(double, double, double, double,
			  double, double, double, bricktype);
	virtual ~BrickData();

	void draw(const Cairo::RefPtr <Cairo::Context>&);

protected:
	bricktype		type;
	double			color[3];
	MathVector2D	position;
	MathVector2D	size;
};

#endif // _BRICK_DATA_H_

