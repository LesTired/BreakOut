/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * paddle-data.cc
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

#include "paddle-data.h"

PaddleData::PaddleData(double pos_x, double pos_y, double width, double height)
:position(pos_x, pos_y)
,velocity(0.0)
,size(width, height)
{
}

void PaddleData::set_movement(movement direction)
{
	static const double abs_vel = 5.0;

	switch(direction)
	{
	case LEFT   :   velocity = -abs_vel;	break;
	case STOP   :   velocity = 0.0;			break;
	case RIGHT  :   velocity = +abs_vel;	break;
	default		:   break;
	}
}

double PaddleData::get_velocity()
{
	return velocity;
}

void PaddleData::draw(const Cairo::RefPtr <Cairo::Context> &cr)
{
	// Draw Paddle
	cr->set_source_rgb(0, 0, 0);
    cr->set_line_width(0.0);
    cr->rectangle(position[0] - size[0]/2.0,
                  position[1],
                  size[0],
                  size[1]);
    cr->stroke_preserve();
	cr->fill();

	// Draw Caps
    cr->arc(position[0] - size[0]/2.0,
            position[1] + size[1]/2.0,
            size[1]/2.0,
            0, 2*M_PI);
    cr->stroke_preserve();
	cr->fill();

    cr->arc(position[0] + size[0]/2.0,
            position[1] + size[1]/2.0,
            size[1]/2.0,
            0, 2*M_PI);
    cr->stroke_preserve();
	cr->fill();
}

PaddleData::~PaddleData()
{
}

