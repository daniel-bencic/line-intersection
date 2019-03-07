#include <vector>
#include <map>
#include <algorithm>

#include "intersection.hpp"

std::vector<std::pair<LineSegment, LineSegment>> compute_intersections(std::vector<LineSegment>& line_segments)
{
	std::vector<Event> events = get_events(line_segments);
	std::map<double, LineSegment> sweep_line;
	std::vector<std::pair<LineSegment, LineSegment>> intersections;

	for (Event event : events)
	{
		if (event.type == EventType::L_ENDPOINT)
		{
			sweep_line[event.line_segment.coordinate] = event.line_segment;
		}
		else if (event.type == EventType::R_ENDPOINT)
		{
			sweep_line.erase(event.line_segment.coordinate);
		}
		else
		{
			std::map<double, LineSegment>::iterator itlow, itup;
			itlow = sweep_line.lower_bound(event.line_segment.end);
			itup = sweep_line.upper_bound(event.line_segment.start);

			for (itlow; itlow != itup; ++itlow)
			{
				intersections.push_back(std::pair<LineSegment, LineSegment>(event.line_segment, itlow->second));
			}
		}
	}

	return intersections;
}

std::vector<Event> get_events(std::vector<LineSegment>& line_segments)
{
	std::vector<Event> events;

	for (LineSegment line_segment : line_segments)
	{
		if (line_segment.orientation == LineSegmentOrientation::VERTICAL)
		{
			Event vls_event;
			vls_event.type = EventType::VLS_COORD;
			vls_event.line_segment = line_segment;
			events.push_back(vls_event);
		}
		else
		{
			Event l_endpoint_event, r_endpoint_event;
			l_endpoint_event.type = EventType::L_ENDPOINT;
			l_endpoint_event.line_segment = line_segment;
			r_endpoint_event.type = EventType::R_ENDPOINT;
			r_endpoint_event.line_segment = line_segment;
			events.push_back(l_endpoint_event);
			events.push_back(r_endpoint_event);
		}
	}

	std::sort(events.begin(), events.end());

	return events;
}
