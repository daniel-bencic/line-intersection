#pragma once

enum class LineSegmentOrientation
{
	VERTICAL = 1,
	HORIZONTAL
};

class LineSegment
{
public:
	LineSegmentOrientation orientation;
	double coordinate; // y-coordinate (horizontal line) or x-coordinate (vetical line)
	double start, end; // y-coordinates (vertical line) or x-coordinates (horizontal line)

	LineSegment();
	LineSegment(LineSegmentOrientation orientation, double coordinate, double start, double end);
	~LineSegment();

private:

};

enum class EventType
{
	L_ENDPOINT = 1,
	R_ENDPOINT,
	VLS_COORD
};

class Event
{
public:
	EventType type;
	LineSegment line_segment;

	Event();
	Event(EventType type, LineSegment line_segment);
	~Event();

	bool operator<(const Event& event) const;

private:

};