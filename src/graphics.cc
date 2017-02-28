/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * graphics.cc
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

#include "graphics.h"

Graphics::Graphics(GameData* dataptr)
:data(dataptr)
{
    Glib::signal_timeout().
	connect(sigc::mem_fun(*this, &Graphics::on_timeout), DRAW_TIME_INTERVAL);

	std::vector<std::string> sys_vars_data = EnvVarVector("XDG_DATA_DIRS");
	for(int i = 0; i < sys_vars_data.size(); i++)
	{
		std::string file = sys_vars_data[i] + "/breakout/grey_bg_small.png";

		try
		{
			bg_image = Cairo::ImageSurface::create_from_png(file);
		}
		catch(const Cairo::logic_error& e)
		{
			//std::cerr << e.what();
		}
		
		if(bg_image)
		{
			break;
		}
	}
}

Graphics::~Graphics()
{
}

bool Graphics::on_draw(const Cairo::RefPtr <Cairo::Context>& cr)
{
    // Necessary setup for drawing text with Pango.
    Pango::FontDescription font;
    font.set_family("Monospace"); font.set_weight(Pango::WEIGHT_BOLD);
    auto layout = create_pango_layout(""); int text_width, text_height;
    layout->set_font_description(font);

    // Draw Background.
    if (!bg_image)
    {
    	cr->set_source_rgb(1.0, 1.0, 1.0);
    }
    else
    {
    	cr->set_source(bg_image, 0, 0);
    }
    cr->rectangle(0.0, 0.0, data->Window_width, data->Window_height);
    cr->stroke_preserve();
    cr->fill();

    // Draw all game objects. The rendering is defered to a member-function
    // within the respective objects class.
    data->Ball.draw(cr);
    data->Paddle.draw(cr);
    data->Level.draw(cr);

    // Draw Text element that shows remaining lives.
    layout->set_text("Lives: " + std::to_string(data->lives));
    layout->get_pixel_size(text_width, text_height);
    cr->set_source_rgba(0.0, 0.0, 0.0, 0.5);
    cr->move_to(data->Window_width  - (text_width  + 5),
                data->Window_height - (text_height + 5));
    layout->show_in_cairo_context(cr);

    // Draw "GameOver" Screen.
    if(data->Game_over)
    {
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.9);
        cr->rectangle(0.0, 0.0, data->Window_width, data->Window_height);
    	cr->stroke_preserve();
    	cr->fill();

        layout->set_text("GAME OVER !!!!!\nNew Game? (Y/N)");
        layout->get_pixel_size(text_width, text_height);
        cr->set_source_rgb(1.0, 0.84, 0.0);
        cr->move_to((data->Window_width  - text_width )/2.0,
                    (data->Window_height - text_height)/2.0);
        layout->show_in_cairo_context(cr);
    }

    // Draw "Paused" Screen.
    if(data->Game_paused)
    {
        cr->set_source_rgba(0.0, 0.0, 0.0, 0.9);
        cr->rectangle(0.0, 0.0, data->Window_width, data->Window_height);
    	cr->stroke_preserve();
    	cr->fill();

        layout->set_text("GAME PAUSED!");
        layout->get_pixel_size(text_width, text_height);
        cr->set_source_rgb(1.0, 0.84, 0.0);
        cr->move_to((data->Window_width  - text_width )/2.0,
                    (data->Window_height - text_height)/2.0);
        layout->show_in_cairo_context(cr);
    }

  	return true;
}

bool Graphics::on_timeout()
{
    // Main call for running the porgram.
    data->propagate_time();

    // Force program to redraw the entire window.
    auto win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                               get_allocation().get_height());
        win->invalidate_rect(r, false);
    }

  	return true;
}


