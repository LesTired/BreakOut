/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ball-data.cc
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

#include "ball-data.h"

BallData::BallData(double r)
:radius(r)
,on_paddle(true)
,velocity({0.0, 0.0})
,trail_length(15)
{
}

bool BallData::is_on_paddle()
{
	return on_paddle;
}

void BallData::set_on_paddle(bool new_value)
{
	on_paddle = new_value;
}

void BallData::set_velocity(MathVector2D new_velocity)
{
	velocity = new_velocity;
}

void BallData::draw(const Cairo::RefPtr <Cairo::Context> &cr)
{
	// Draw trail of Ball
	if(trail_length > 0)
	{
		for(int i = 0; i < trail.size(); i++)
		{
			cr->set_source_rgba(0.8, 0, 0, ((double) i/trail.size()) / 1.5);
		    cr->set_line_width(0.0);
		    cr->arc(trail[i][0],
		            trail[i][1],
		            radius,
		            0, 2*M_PI);
		    cr->stroke_preserve();
			cr->fill();
		}
	}

	// Draw Ball
	cr->set_source_rgb(0.3, 0, 0);
    cr->set_line_width(1.0);
    cr->arc(position[0],
            position[1],
            radius,
            0, 2*M_PI);
    cr->stroke_preserve();
	cr->set_source_rgb(0.8, 0, 0);
	cr->fill();
}

BallData::~BallData()
{
}

