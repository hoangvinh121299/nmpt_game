#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObj.h"
#include "Sprites.h"

CGameObj::CGameObj()
{
	x = y = 0;
	vx = 0.07f;
}

void CGameObj::Update(DWORD dt)
{
	x += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0)) vx = -vx;
}

void CGameObj::Render()
{
	LPANIMATION ani;
	if (vx > 0) ani = animations[0]; else ani = animations[1];
	//ani = animations[0];
	ani->Render(x, y);
}


void CGameObj::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}



CGameObj::~CGameObj()
{
}