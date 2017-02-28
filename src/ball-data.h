/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ball-data.h
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

#ifndef _BALL_DATA_H_
#define _BALL_DATA_H_

#include <vector>
#include <cmath>
#include <iostream>

#include <cairomm/context.h>

#include "math-vector2-d.h"

class PaddleData;
class BrickData;
class GameData;
class CollisionModelData;

class BallData
{
friend class GameData;
friend class CollisionModelData;
public:
	BallData(double);
	virtual ~BallData();

	void set_velocity(MathVector2D);
	bool is_on_paddle();
	void set_on_paddle(bool);
	void draw(const Cairo::RefPtr <Cairo::Context>&);

protected:
	double 			radius;
	MathVector2D 	position;
	MathVector2D 	velocity;
	bool 			on_paddle;

	int trail_length;
	std::vector<MathVector2D> trail;
};

#endif // _BALL_DATA_H_

