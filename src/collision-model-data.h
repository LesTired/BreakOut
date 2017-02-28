/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * collision-model-data.h
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

#ifndef _COLLISION_MODEL_DATA_H_
#define _COLLISION_MODEL_DATA_H_

#include <vector>
#include <cmath>

#include "math-vector2-d.h"
#include "ball-data.h"
#include "paddle-data.h"
#include "brick-data.h"
#include "level-data.h"

class CollisionModelData
{
public:
	CollisionModelData();
	virtual ~CollisionModelData();

	double get_time_of_collision();
	double get_reflection_velocity_x();
	double get_reflection_velocity_y();

	void operator()(const BallData&, const MathVector2D&, const MathVector2D&);
	void operator()(const BallData&, const MathVector2D&, const double);
	void operator()(const BallData&, const MathVector2D&);
	void operator()(const BallData&, const BrickData&);
	void operator()(const BallData&, const PaddleData&);

protected:
	double time_of_collision;
	MathVector2D velocity_s;
};

#endif // _COLLISION_MODEL_DATA_H_

