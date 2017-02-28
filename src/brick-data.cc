/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * brick-data.cc
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

#include "brick-data.h"

BrickData::BrickData(double pos_x, double pos_y, double width, double height)
:position(pos_x, pos_y)
,size(width, height)
,type(NORMAL)
,color{0.5, 0.5, 0.5}
{
}

BrickData::BrickData(double pos_x, double pos_y, double width, double height,
					 double col_r, double col_g, double col_b, bricktype bt)
:position(pos_x, pos_y)
,size(width, height)
,type(bt)
,color{col_r, col_g, col_b}
{
}

void BrickData::draw(const Cairo::RefPtr <Cairo::Context> &cr)
{
	switch(type)
	{
	case EMPTY	: 	break;
	case NORMAL : 	// White background
					cr->set_line_width(0.0);
					cr->set_source_rgb(1.0, 1.0, 1.0);
					cr->rectangle(position[0], position[1], size[0], size[1]);
					cr->stroke_preserve();
					cr->fill();

					// Texture
					cr->set_line_width(0.0);
					cr->set_source_rgb(0.3, 0.3, 0.3);
					cr->move_to(position[0], position[1] + size[1]);
					cr->line_to(position[0] + size[0], position[1] + size[1]);
					cr->line_to(position[0] + size[0], position[1]);
					cr->close_path();
					cr->stroke_preserve();
					cr->fill();

					// Block itself
					cr->set_line_width(0.8);
					cr->set_source_rgba(0.3, 0.3, 0.3, 0.7);
					cr->rectangle(position[0], position[1], size[0], size[1]);
					cr->stroke_preserve();
					cr->set_source_rgba(color[0], color[1], color[2], 0.7);
					cr->fill();

					break;
	case SOLID	:	// White background
					cr->set_line_width(0.0);
					cr->set_source_rgb(1.0, 1.0, 1.0);
					cr->rectangle(position[0], position[1], size[0], size[1]);
					cr->stroke_preserve();
					cr->fill();

					// Texture
					cr->set_line_width(0.0);
					cr->set_source_rgba(0.3, 0.3, 0.3, 0.7);
					cr->move_to(position[0], position[1] + size[1]);
					cr->line_to(position[0] + size[0], position[1] + size[1]);
					cr->line_to(position[0] + size[0], position[1]);
					cr->close_path();
					cr->stroke_preserve();
					cr->fill();
					cr->move_to(position[0], position[1]);
					cr->line_to(position[0] + size[0], position[1] + size[1]);
					cr->line_to(position[0], position[1] + size[1]);
					cr->close_path();
					cr->stroke_preserve();
					cr->fill();

					// Block itself
					cr->set_line_width(1.5);
					cr->set_source_rgba(0.2, 0.2, 0.2, 0.7);
					cr->rectangle(position[0], position[1], size[0], size[1]);
					cr->stroke_preserve();
					cr->fill();
					break;
	default		: 	break;
	}
}

BrickData::~BrickData()
{
}

