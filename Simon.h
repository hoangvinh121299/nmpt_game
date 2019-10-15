#pragma once
#include "GameObj.h"
#include "debug.h"
class CSimon:public CGameObj
{
public:
	float vx = SIMON_WALKING_SPEED;
public:
	CSimon();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt);
	void Render();
	~CSimon();
};

