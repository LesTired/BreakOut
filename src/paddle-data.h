/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * paddle-data.h
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

#ifndef _PADDLE_DATA_H_
#define _PADDLE_DATA_H_

#include <vector>
#include <cmath>
#include <iostream>

#include <cairomm/context.h>

#include "math-vector2-d.h"

enum movement{LEFT, RIGHT, STOP};

class GameData;
class CollisionModelData;

class PaddleData
{
friend class GameData;
friend class CollisionModelData;
public:
	PaddleData(double, double, double, double);
	virtual ~PaddleData();

	void draw(const Cairo::RefPtr <Cairo::Context>&);
	void set_movement(movement);
	double get_velocity();

protected:
	MathVector2D 	position;
	double			velocity;
	MathVector2D	size;
};

#endif // _PADDLE_DATA_H_

