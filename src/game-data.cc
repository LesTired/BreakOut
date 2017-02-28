/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * game-data.cc
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

#include "game-data.h"

GameData::GameData(int WINDOW_WIDTH, int WINDOW_HEIGHT)
:Window_width(WINDOW_WIDTH)
,Window_height(WINDOW_HEIGHT)
,Ball(4.0)
,Paddle(WINDOW_WIDTH/2.0, WINDOW_HEIGHT-30.0, 55.0, 7.0)
,Level(WINDOW_WIDTH, WINDOW_HEIGHT * 0.5, 10, 10)
,lives(3)
,Game_over(false)
,Game_paused(false)
{
	// Scan the userdata directories for Level-files.
	std::vector<std::string> sys_vars_data = EnvVarVector("XDG_DATA_DIRS");
	for(int i = 0; i < sys_vars_data.size(); i++)
	{
		std::string dir = sys_vars_data[i] + "/breakout/levels/";
		level_files = dir_reader(dir);

		if(level_files.size() != 0)
		{
			Level = LevelData(WINDOW_WIDTH, WINDOW_HEIGHT * 0.5, level_files[0]);
			break;
		}
	}
}

GameData::~GameData()
{
}

void GameData::propagate_time()
{
	// Halt game if Game Over!
	if(Game_over == true)
	{
		return;
	}

	// Halt game if Paused!
	if(Game_paused == true)
	{
		return;
	}

	// Mange the balls trail.
	if(Ball.on_paddle == false)
	{
		Ball.trail.push_back(Ball.position);
	}
	if(Ball.trail.size() > Ball.trail_length)
	{
		Ball.trail.erase(Ball.trail.begin());
	}

	// If Ball hasn't been fired from the paddle yet, Ball follows Paddle.
	if(Ball.on_paddle == true)
	{
		Ball.position[0] = Paddle.position[0];
		Ball.position[1] = Paddle.position[1] - Ball.radius;
	}

	// Test for lost ball.
	if(Ball.position[1] >= Window_height + Ball.radius + 20.0)
	{
		lives--;
		if(lives > 0)
		{
			Ball = BallData(Ball.radius);
		}
		else
		{
			Game_over = true;
		}
	}

	// Initialize collision Functor for this timestep.
	CollisionModelData this_timestep_CMD;

	// Collision check on walls.
	this_timestep_CMD(Ball,
					  {0.0, (double)Window_height}, {0.0, 0.0});
	this_timestep_CMD(Ball,
					  {0.0, 0.0}, {(double)Window_width, 0.0});
	this_timestep_CMD(Ball,
					  {(double)Window_width, 0.0},
					  {(double)Window_width, (double)Window_height});
	/*this_timestep_CMD(Ball,
					  {0.0, (double)Window_height},
					  {(double)Window_width, (double)Window_height});*/

	// Collision check on paddle. Ball can get stuck in paddle if not prevented.
	static int anti_paddle_stuck = 0;
	if(anti_paddle_stuck == 0)
	{
		double temp = this_timestep_CMD.get_time_of_collision();
		
		this_timestep_CMD(Ball, Paddle);

		if(this_timestep_CMD.get_time_of_collision() != temp)
		{
			anti_paddle_stuck = 25;
		}
	}
	else anti_paddle_stuck--;

	// Collision check on bricks.
	int Block_hit_x = -1;
	int Block_hit_y = -1;
	double collision_time_save = this_timestep_CMD.get_time_of_collision();
	for(int x = 0; x < Level.BrickField.size(); x++)
	{
		for(int y = 0; y < Level.BrickField.begin()->size(); y++)
		{
			// Skip the block if already destroyed.
			if(Level.BrickField[x][y].type == EMPTY) continue;

			this_timestep_CMD(Ball, Level.BrickField[x][y]);

			if(this_timestep_CMD.get_time_of_collision() < collision_time_save)
			{
				collision_time_save = this_timestep_CMD.get_time_of_collision();
				Block_hit_x = x;
				Block_hit_y = y;
			}
		}
	}

	// Move the Paddle, but also make it stop at the window borders!
	if(this_timestep_CMD.get_time_of_collision() >= 1.0)
	{
		Paddle.position[0] += Paddle.velocity;
	}
	else
	{
		Paddle.position[0] += this_timestep_CMD.get_time_of_collision() *
							  Paddle.velocity;
	}

	if(Paddle.position[0] - Paddle.size[0]/2.0 -
							Paddle.size[1]/2.0 < 0.0)
	{
		Paddle.position[0] = Paddle.size[0]/2.0 +
							 Paddle.size[1]/2.0;
		Paddle.velocity = 0.0;
	}

	if(Paddle.position[0] + Paddle.size[0]/2.0 +
							Paddle.size[1]/2.0 > Window_width)
	{
		Paddle.position[0] = Window_width - Paddle.size[0]/2.0 -
											Paddle.size[1]/2.0;
		Paddle.velocity = 0.0;
	}

	// Apply movement and change of velocity to the ball.
	if(this_timestep_CMD.get_time_of_collision() >= 1.0)
	{
		Ball.position += Ball.velocity;
	}
	else
	{
		Ball.position += this_timestep_CMD.get_time_of_collision() *
						 Ball.velocity;

		Ball.set_velocity({this_timestep_CMD.get_reflection_velocity_x(),
						   this_timestep_CMD.get_reflection_velocity_y()});

		if((Block_hit_x != -1) && (Block_hit_y != -1) &&
		(Level.BrickField[Block_hit_x][Block_hit_y].type != SOLID))
		{
			Level.BrickField[Block_hit_x][Block_hit_y].type = EMPTY;
		}
	}

	// Final corrections for the balls velocity are necessary, because the 
	// collision model is too strict to yield a playable game!
	if(Ball.on_paddle == true) return;
	if(fabs(Ball.velocity[0]) < 0.5)
	{
		Ball.velocity[0] = (Ball.velocity[0] < 0.0) ? -0.5 : 0.5;
	}
	if(fabs(Ball.velocity[1]) < 0.5)
	{
		Ball.velocity[1] = (Ball.velocity[1] < 0.0) ? -0.5 : 0.5;
	}
	if(Ball.velocity.norm() > 3.5 || Ball.velocity.norm() < 2.0)
	{
		Ball.velocity *= 3.5/Ball.velocity.norm();
	}

	// Check if the Level is completed yet.
	int Brick_cnt = 0;
	for(auto&& i : Level.BrickField) for(auto&& j : i)
		if(j.type == NORMAL) Brick_cnt++;

	if(Brick_cnt == 0)
	{
		if(level_files.size() != 0)
		{
			level_files.erase(level_files.begin());
		}
		if(level_files.size() <= 0)
		{
			Game_over = true;
			return;
		}
		Level = LevelData(Window_width, Window_height * 0.5, level_files[0]);
		Ball = BallData(Ball.radius);
	}
}