#include "Hit.h"

bool ISHit(D3DXVECTOR3 ball, D3DXVECTOR3 goal, float ballw,float goalw)
{
	float x = goal.x - ball.x-ballw;
	float z = goal.z-ball.z;
	float l = x*x + z*z;
	if (ball.y<=1)
	{
		return l<(ballw + goalw)*(ballw + goalw);
	}
	else
	{
		return false;
	}
}
