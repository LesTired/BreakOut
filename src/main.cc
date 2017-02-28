/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
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

#include <gtkmm.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "config.h"


#ifdef ENABLE_NLS
#  include <libintl.h>
#endif


#include "main-window.h"
   
int
main (int argc, char *argv[])
{
	// Seed the random number generator.
	srand(time(NULL));

	// Set up and Start GTK.
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	MainWindow window;
	app->run(window);

	return 0;
}

