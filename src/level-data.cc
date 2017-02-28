/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * level-data.cc
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

#include "level-data.h"

LevelData::LevelData(double Field_size_x, double Field_size_y,
		  	 		 int amount_x, int amount_y)
{
	double Brick_size_x = Field_size_x / amount_x;
	double Brick_size_y = Field_size_y / amount_y;

	for(int y = 0; y < amount_y; y++)
	{
		std::vector<BrickData> Brick_Row;
		for(int x = 0; x < amount_x; x++)
		{
			// Random color generator.
			double rand_r = (1 + rand() % 256) * (1.0/256.0);
			double rand_g = (1 + rand() % 256) * (1.0/256.0);
			double rand_b = (1 + rand() % 256) * (1.0/256.0);

			BrickData ProtoBrick(x * Brick_size_x,
								 y * Brick_size_y,
								 Brick_size_x, Brick_size_y,
								 rand_r, rand_g, rand_b,
								 NORMAL);
			Brick_Row.push_back(ProtoBrick);
		}
		BrickField.push_back(Brick_Row);
	}
}

LevelData::LevelData(double Field_size_x,
					 double Field_size_y, std::string filename)
{
	std::string line;
	std::vector<std::string> all_lines;
	std::ifstream file(filename, std::ios::in);

	if(! file)
	{
		std::cerr << "Error opening input file: "
				  << "File does not exist."
				  << "\nCreate standard level instead!" << std::endl;
		*this = LevelData(Field_size_x, Field_size_y, 10, 10);
		return;
	}

	int amount_x = 100;
	int amount_y = 0;

	while(std::getline(file, line))
	{
		if(line.size() < amount_x)
		{
			amount_x = line.size();
		}

		amount_y++;
		all_lines.push_back(line);

		if(amount_y > 25) break;
	}
	file.close();

	if(amount_x <= 0 || amount_y <= 0 || amount_x > 25 || amount_y > 25)
	{
		std::cerr << "Error opening input file: "
				  << "Brickfield of unreasonable size."
				  << "\nCreate standard level instead!" << std::endl;
		*this = LevelData(Field_size_x, Field_size_y, 10, 10);
		return;
	}

	double Brick_size_x = Field_size_x / amount_x;
	double Brick_size_y = Field_size_y / amount_y;

	for(int y = 0; y < amount_y; y++)
	{
		line = all_lines[y];

		std::vector<BrickData> Brick_Row;
		for(int x = 0; x < amount_x; x++)
		{
			// Random color generator.
			double rand_r = (1 + rand() % 256) * (1.0/256.0);
			double rand_g = (1 + rand() % 256) * (1.0/256.0);
			double rand_b = (1 + rand() % 256) * (1.0/256.0);

			BrickData ProtoBrick(x * Brick_size_x,
								 y * Brick_size_y,
								 Brick_size_x, Brick_size_y,
								 rand_r, rand_g, rand_b,
								 (line.at(x) == 'N' ? NORMAL :
								  line.at(x) == 'S' ? SOLID	 :
								  line.at(x) == 'E' ? EMPTY  : EMPTY));

			Brick_Row.push_back(ProtoBrick);
		}
		BrickField.push_back(Brick_Row);
	}
}

void LevelData::draw(const Cairo::RefPtr <Cairo::Context> &cr)
{
	for(int y = 0; y < BrickField.size(); y++)
	{
		for(int x = 0; x < BrickField[0].size(); x++)
		{
			BrickField[y][x].draw(cr);
		}
	}
}

LevelData::~LevelData()
{
}
