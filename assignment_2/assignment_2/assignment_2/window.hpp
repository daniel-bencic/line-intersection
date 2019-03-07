#pragma once
#include <vector>

#include <SDL.h>

#include "geometric_objects.hpp"

class Window
{
public:
	int width = 0, height = 0, margin = 0;
	double x_scale = 0, y_scale = 0;
	bool initialized = false;

	Window(int width, int heigth, int margin);
	~Window();
	void handle_events();
	void render(std::vector<LineSegment>& line_segments, std::vector<std::pair<LineSegment, LineSegment>>& intersections);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	void draw_coordinate_system();
	void draw_line_segments(std::vector<LineSegment>& line_segments);
	void draw_intersections(std::vector<std::pair<LineSegment, LineSegment>>& intersections);
	double calc_x_scale(std::vector<LineSegment>& line_segments);
	double calc_y_scale(std::vector<LineSegment>& line_segments);
	SDL_Point sdl_point_from_coordinates(double x, double y);
};