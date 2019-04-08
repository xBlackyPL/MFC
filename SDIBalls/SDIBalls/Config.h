#pragma once
#include <map>

namespace BallsConfiguration
{
	const std::map<std::string, COLORREF> Colors{
		{"Black", RGB(0, 0, 0)},
		{"White", RGB(255, 255, 255)},
		{"Red", RGB(255, 0, 0)},
		{"Green", RGB(0, 255, 0)},
		{"Blue", RGB(0, 0, 255)},
		{"Orange", RGB(255, 165, 0)},
		{"Cyan", RGB(0, 255, 255)},
		{"GreenYellow", RGB(173, 255, 47)}
	};

	const unsigned char minimal_number_of_balls = 3;
	const unsigned char maximal_number_of_balls = 10;
	
	const unsigned char default_ball_x_axis_velocity = 1;
	const unsigned char default_ball_y_axis_velocity = 1;

	const unsigned char minimal_ball_x_axis_velocity = 1;
	const unsigned char maximal_ball_x_axis_velocity = 10;

	const unsigned char minimal_ball_y_c_axis_velocity = 1;
	const unsigned char maximal_ball_y_axis_velocity = 10;

	const unsigned char minimal_ball_radius = 30;
	const unsigned char maximal_ball_radius = 120;

	const unsigned char default_ball_x = 300;
	const unsigned char default_ball_y = 300;
}
