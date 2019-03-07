#pragma once
#include <utility>
#include <vector>

#include "geometric_objects.hpp"

std::vector<std::pair<LineSegment, LineSegment>> compute_intersections(std::vector<LineSegment>& line_segments);
std::vector<Event> get_events(std::vector<LineSegment>& line_segments);
