/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * env-vectorize.cc
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

#include "env-vectorize.h"

std::vector<std::string> EnvVarVector(std::string input)
{
	std::vector<std::string> sys_vars;
	
	char *sys_vars_char = std::getenv(input.c_str());
	std::string sys_vars_str;
	
	try
	{
		std::string sys_vars_str_temp(sys_vars_char);
		sys_vars_str = sys_vars_str_temp;
	}
	catch(std::logic_error &e)
	{
		std::cerr<<e.what()<<std::endl;
	}
	
	while (!sys_vars_str.empty())
	{
		std::size_t found = sys_vars_str.rfind(":");
			
		if(found!=std::string::npos)
		{
			std::string partial = sys_vars_str.substr(found + 1);
			sys_vars.push_back(partial);
				
			for(int i = 0; i < (partial.size() + 1); i++)
			{
				sys_vars_str.pop_back();
			}
		}
		else
		{
			sys_vars.push_back(sys_vars_str);
			sys_vars_str.clear();
		}
	}
	
	return sys_vars;
}