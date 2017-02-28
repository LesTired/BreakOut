/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main-window.h
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

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

// Parameters for fixed windowsize.
#define WINDOW_WIDTH  520
#define WINDOW_HEIGHT 400

#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "graphics.h"
#include "game-data.h"

class MainWindow: public Gtk::Window 
{
public:
	MainWindow();
	virtual ~MainWindow();

protected:
	GameData game;
	Graphics game_graphics;
	bool on_key_event(GdkEventKey *key_event);
};

#endif // _MAIN_WINDOW_H_

