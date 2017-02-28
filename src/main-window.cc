/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main-window.cc
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

#include "main-window.h"

MainWindow::MainWindow()
:game(WINDOW_WIDTH, WINDOW_HEIGHT)
,game_graphics(&game)
{
	set_title("BreakOut");
	set_size_request(WINDOW_WIDTH, WINDOW_HEIGHT);
	set_resizable(false);

	signal_key_press_event().
	connect(sigc::mem_fun(*this, &MainWindow::on_key_event), false);
	signal_key_release_event().
	connect(sigc::mem_fun(*this, &MainWindow::on_key_event), false);

	add(game_graphics);

	show_all_children();
}

MainWindow::~MainWindow()
{
}

bool MainWindow::on_key_event(GdkEventKey *key_event)
{
	// If the Game is over it can be restarted with pressing Y/y or the window
	// can be closed by pressing N/n.
	if(game.Game_over)
	{
		if(key_event->keyval == GDK_KEY_n || key_event->keyval == GDK_KEY_N)
		{
			this->close();
		}

		if(key_event->keyval == GDK_KEY_y || key_event->keyval == GDK_KEY_Y)
		{
			game = GameData(WINDOW_WIDTH, WINDOW_HEIGHT);
		}

		return false;
	}

	// In-Game Controls.
	// Key-Press and Key-Release actions are decoupled to prevent the jumpy
	// response of the Paddle which would occur due to Key-locking.
	switch(key_event->keyval)
	{
	case GDK_KEY_a		:
	case GDK_KEY_Left	: 	if(key_event->type == GDK_KEY_PRESS)
							{
								game.Paddle.set_movement(LEFT);
							}

							if(key_event->type == GDK_KEY_RELEASE &&
							game.Paddle.get_velocity() < 0.0)
							{
								game.Paddle.set_movement(STOP);
							}

							break;
	case GDK_KEY_d	 	:
	case GDK_KEY_Right	: 	if(key_event->type == GDK_KEY_PRESS)
							{
								game.Paddle.set_movement(RIGHT);
							}

							if(key_event->type == GDK_KEY_RELEASE &&
							game.Paddle.get_velocity() > 0.0)
							{
								game.Paddle.set_movement(STOP);
							}

							break;
	case GDK_KEY_p 		: 	if(key_event->type == GDK_KEY_PRESS)
							{
								game.Game_paused = !game.Game_paused;
							}
						    break;
	case GDK_KEY_space	:	if(game.Ball.is_on_paddle())
							{
								game.Ball.set_velocity({2.5, -2.5});
								game.Ball.set_on_paddle(false);
							}

							break;
	case GDK_KEY_Escape	:	this->close(); break;
	default 			: 	break;
	}

	return false;
}



