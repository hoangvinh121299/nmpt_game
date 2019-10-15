#include "Simon.h"

CSimon::CSimon()
{
}
void CSimon::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x;
	b = y;
}
void CSimon::Update(DWORD dt)
{
	CGameObj::Update(dt);
	x += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) vx = -vx;
}
void CSimon::Render()
{
	LPANIMATION ani;
	if (vx > 0) ani = animations[0]; else ani = animations[1];
	//ani = animations[0];
	ani->Render(x, y);
}
CSimon::~CSimon()
{
}
