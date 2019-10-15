#include "StaticObj.h"

void CStaticObj::Update(DWORD dt)
{
	CGameObj::Update(dt);
}

void CStaticObj::Render()
{
	LPANIMATION ani;
	if (vx > 0) ani = animations[0]; else ani = animations[1];
	//ani = animations[0];
	ani->Render(x, y);
}
