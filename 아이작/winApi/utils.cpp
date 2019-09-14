#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	//�� �� ������ �Ÿ��� ���Ѵ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		return sqrt(x * x + y * y);
	}

	//Start���� End������ ���� �������� ���Ѵ�
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);
		float angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;
		return angle;
	}
}
