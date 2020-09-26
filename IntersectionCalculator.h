#pragma once


// This class computes the intersection of a line with an indicated circle.
// The circle and the starting point of the line are generated in the constructor.
// The heading of the line can by dynamically adjusted.
class IntersectionCalculator
{
public:
	// Constructor takes the parameters for the different values.
	IntersectionCalculator(const float centerCircle[], const float radiusCircle);
	
	// Compute the intersections.
	void ComputeIntersectionWithLine(const float pointLine[], const float lineDirection[]);

	// Extraxt the amount of calculated intersection points.
	int GetAmountOfIntersectionPoints() const;

	// Extracts the intersection point.
	void GetIntersectionPoint(int index, float position[]);

private:
	// The center point of the circle.
	float m_centerCircle[2];
	// The radius of the circle.
	float m_circleRadius;


	// The amount of intersection points we have.
	int m_computedIntersectionPoints;
	
	// The intersection points we compute.
	float m_intersectionPoints[2][2];
};

