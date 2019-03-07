#include <vector>

#include <SDL.h>

#include "geometric_objects.hpp"
#include "intersection.hpp"
#include "window.hpp"

int main(int argc, char *args[])
{
	LineSegment s0(LineSegmentOrientation::HORIZONTAL, 5, 1, 3);
	LineSegment s1(LineSegmentOrientation::HORIZONTAL, 2, 0, 8);
	LineSegment s2(LineSegmentOrientation::HORIZONTAL, 3, -3, 7);
	LineSegment s3(LineSegmentOrientation::HORIZONTAL, 2.5, -4.2, 7);
	LineSegment s4(LineSegmentOrientation::VERTICAL, 2, 5, 1);
	LineSegment s5(LineSegmentOrientation::VERTICAL, 6, 4, 2);
	LineSegment s6(LineSegmentOrientation::VERTICAL, -2.5, 4, 2);
	LineSegment s7(LineSegmentOrientation::HORIZONTAL, -4, -7, 7);
	LineSegment s8(LineSegmentOrientation::VERTICAL, -1, -2, -5);
	LineSegment s9(LineSegmentOrientation::VERTICAL, 6, -3.9, -5.8);
	LineSegment s10(LineSegmentOrientation::VERTICAL, 0, 3, -3);
	std::vector<LineSegment> line_segments = { s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10 };

	std::vector<std::pair<LineSegment, LineSegment>> intersections = compute_intersections(line_segments);

	Window window(801, 801, 50);

	while (window.initialized)
	{
		window.handle_events();
		window.render(line_segments, intersections);
	}

	return 0;
}