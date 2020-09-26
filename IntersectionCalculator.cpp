#include "IntersectionCalculator.h"
#include <math.h>


// Constructor takes the parameters for the different values.
// centerCircle: The fixed position of the circle for intersection calculation.
// radiusCircle: The radius of the circle we use for intersection calculation.
IntersectionCalculator::IntersectionCalculator(const float centerCircle[], const float radiusCircle)
{
	m_centerCircle[0] = centerCircle[0];
	m_centerCircle[1] = centerCircle[1];
	m_circleRadius = radiusCircle;
	m_computedIntersectionPoints = 0;
}
	
// Compute the intersections.
// pointLine: A point on the line.
// lineDirection: The direction of the line that is beeing taken.
void IntersectionCalculator::ComputeIntersectionWithLine(const float pointLine[], const float lineDirection[])
{
	float h[2];

	h[0] = pointLine[0] - m_centerCircle[0];
	h[1] = pointLine[1] - m_centerCircle[1];

	float b = 2.0f * (lineDirection[0] * h[0] + lineDirection[1] * h[1]);
	float c = (h[0] * h[0] + h[1] * h[1]) - m_circleRadius * m_circleRadius;

	float subSqrt = b * b - 4.0f * c;

	if (subSqrt < 0.0f) 
	{
		m_computedIntersectionPoints = 0;

		return;
	}

	if (subSqrt == 0.0f) 
	{
		m_computedIntersectionPoints = 1;

		float param = -b / 2.0f;

		m_intersectionPoints[0][0] = pointLine[0] + param * lineDirection[0];
		m_intersectionPoints[0][1] = pointLine[1] + param * lineDirection[1];

		return;
	}

	float sqrtExpression = sqrtf(subSqrt);

	m_computedIntersectionPoints = 2;

	float param = (-b + sqrtExpression) / 2.0f;
	m_intersectionPoints[0][0] = pointLine[0] + param * lineDirection[0];
	m_intersectionPoints[0][1] = pointLine[1] + param * lineDirection[1];

	param = (-b - sqrtExpression) / 2.0f;
	m_intersectionPoints[1][0] = pointLine[0] + param * lineDirection[0];
	m_intersectionPoints[1][1] = pointLine[1] + param * lineDirection[1];


}

// Extraxt the amount of calculated intersection points.
int IntersectionCalculator::GetAmountOfIntersectionPoints() const
{
	return m_computedIntersectionPoints;
}

// Extracts the intersection point.
// index: The index of the position we are interested in.
// position: here we fill in the position we want to render.
void IntersectionCalculator::GetIntersectionPoint(int index, float position[])
{
	position[0] = m_intersectionPoints[index][0];
	position[1] = m_intersectionPoints[index][1];
}