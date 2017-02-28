/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * dir-reader.cc
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

#include "dir-reader.h"

std::vector<std::string> dir_reader(std::string dir_str)
{
	std::vector<std::string> files;

	DIR           *d;
    struct dirent *dir;
    d = opendir(dir_str.c_str());

    if(d)
	{
        while((dir = readdir(d)) != NULL)
		{
            if(dir->d_type != DT_DIR)
			{
				files.push_back(dir_str + "/" + (std::string)dir->d_name);
            }
        }
        closedir(d);
    }
	std::sort(files.begin(), files.end());

	return files;
}

