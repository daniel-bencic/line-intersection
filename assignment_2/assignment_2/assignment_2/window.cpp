#include <vector>

#include<SDL.h>

#include "geometric_objects.hpp"
#include "window.hpp"

Window::Window(int width, int height, int margin) : width(width), height(height), margin(margin)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Convex Hull", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Renderer: %s", SDL_GetError());
		return;
	}

	initialized = true;
}

void Window::handle_events()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			initialized = false;
		}
	}
}

void Window::render(std::vector<LineSegment>& line_segments, std::vector<std::pair<LineSegment, LineSegment>>& intersections)
{
	x_scale = calc_x_scale(line_segments);
	y_scale = calc_y_scale(line_segments);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	draw_coordinate_system();
	draw_line_segments(line_segments);
	draw_intersections(intersections);

	SDL_RenderPresent(renderer);
}

void Window::draw_coordinate_system()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 0, (height / 2) + 1, width, (height / 2) + 1);
	SDL_RenderDrawLine(renderer, (width / 2) + 1, 0, (width / 2) + 1, height);
}

void Window::draw_intersections(std::vector<std::pair<LineSegment, LineSegment>>& intersections)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	for (std::pair<LineSegment, LineSegment> intersection : intersections)
	{
		SDL_Point p = sdl_point_from_coordinates(intersection.first.coordinate, intersection.second.coordinate);
		SDL_Rect rect;
		rect.x = p.x - 1;
		rect.y = p.y - 1;
		rect.h = 3;
		rect.w = 3;
		SDL_RenderDrawRect(renderer, &rect);
	}
}

void Window::draw_line_segments(std::vector<LineSegment>& line_segments)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_Point p0, p1;

	for (LineSegment line_segment : line_segments)
	{
		if (line_segment.orientation == LineSegmentOrientation::HORIZONTAL)
		{
			p0 = sdl_point_from_coordinates(line_segment.start, line_segment.coordinate);
			p1 = sdl_point_from_coordinates(line_segment.end, line_segment.coordinate);
			SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
		}
		else
		{
			p0 = sdl_point_from_coordinates(line_segment.coordinate, line_segment.start);
			p1 = sdl_point_from_coordinates(line_segment.coordinate, line_segment.end);
			SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
		}
		
	}
}

double Window::calc_x_scale(std::vector<LineSegment>& line_segments)
{
	double max_x_abs = 0;

	for (LineSegment line_segment : line_segments)
	{
		if (line_segment.orientation == LineSegmentOrientation::HORIZONTAL)
		{
			max_x_abs = max_x_abs < abs(line_segment.start) ? abs(line_segment.start) : max_x_abs;
			max_x_abs = max_x_abs < abs(line_segment.end) ? abs(line_segment.end) : max_x_abs;
		}
		else
		{
			max_x_abs = max_x_abs < abs(line_segment.coordinate) ? abs(line_segment.coordinate) : max_x_abs;
		}
	}

	return ((width - 1 - margin) / 2) / max_x_abs;
}

double Window::calc_y_scale(std::vector<LineSegment>& line_segments)
{
	double max_y_abs = 0;

	for (LineSegment line_segment : line_segments)
	{
		if (line_segment.orientation == LineSegmentOrientation::VERTICAL)
		{
			max_y_abs = max_y_abs < abs(line_segment.start) ? abs(line_segment.start) : max_y_abs;
			max_y_abs = max_y_abs < abs(line_segment.end) ? abs(line_segment.end) : max_y_abs;
		}
		else
		{
			max_y_abs = max_y_abs < abs(line_segment.coordinate) ? abs(line_segment.coordinate) : max_y_abs;
		}
	}

	return ((height - 1 - margin) / 2) / max_y_abs;
}

SDL_Point Window::sdl_point_from_coordinates(double x, double y)
{
	SDL_Point sdl_point;

	sdl_point.x = (width / 2 + 1) + x * x_scale;
	sdl_point.y = (height / 2 + 1) - y * y_scale;

	return sdl_point;
}

Window::~Window() 
{ 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}