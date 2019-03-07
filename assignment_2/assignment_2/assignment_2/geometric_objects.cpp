#include "geometric_objects.hpp"

LineSegment::LineSegment() { }

LineSegment::LineSegment(LineSegmentOrientation orientation, double coordinate, double start_point, double end_point) 
	: orientation(orientation), coordinate(coordinate), start(start_point), end(end_point) { }

LineSegment::~LineSegment() { }

Event::Event() { }

Event::Event(EventType type, LineSegment line_segment)
	: type(type), line_segment(line_segment) { }

bool Event::operator<(const Event& event) const 
{
	double x1 = 0, x2 = 0;
	switch (this->type)
	{
	case EventType::L_ENDPOINT:
		x1 = this->line_segment.start;
		break;
	case EventType::R_ENDPOINT:
		x1 = this->line_segment.end;
		break;
	case EventType::VLS_COORD:
		x1 = this->line_segment.coordinate;
		break;
	default:
		break;
	}

	switch (event.type)
	{
	case EventType::L_ENDPOINT:
		x2 = event.line_segment.start;
		break;
	case EventType::R_ENDPOINT:
		x2 = event.line_segment.end;
		break;
	case EventType::VLS_COORD:
		x2 = event.line_segment.coordinate;
		break;
	default:
		break;
	}

	return x1 < x2;
}

Event::~Event() { }
