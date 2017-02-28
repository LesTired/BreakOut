/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * graphics.h
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

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

// Time interval for redrawing the Window in ms.
#define DRAW_TIME_INTERVAL 15

#include <gtkmm/drawingarea.h>
#include <glibmm/main.h>
#include <cairomm/context.h>
#include <cstdlib>
#include <vector>
#include <string>

#include "game-data.h"
#include "env-vectorize.h"

class Graphics: public Gtk::DrawingArea 
{
public:
	Graphics(GameData*);
	virtual ~Graphics();

protected:
	Cairo::RefPtr<Cairo::Surface> bg_image; 
	bool on_draw(const Cairo::RefPtr <Cairo::Context>& cr) override;
	bool on_timeout();
	GameData* data;

private:

};

#endif // _GRAPHICS_H_
