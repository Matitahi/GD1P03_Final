//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "enemy.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEnemy::CEnemy(int _iType)
	: m_bHit(false)
{
	m_iType = _iType;
}

CEnemy::CEnemy()
	: m_bHit(false)
{

}

CEnemy::~CEnemy()
{

}

bool
CEnemy::Initialise()
{
	if (m_iType == 1)
	{
		VALIDATE(CEntity::Initialise(IDB_ENEMY1_1SPRITE, IDB_ENEMY1_1MASK));
	}
	else if (m_iType == 2)
	{
		VALIDATE(CEntity::Initialise(IDB_ENEMY2_1SPRITE, IDB_ENEMY2_1MASK));
	}
	else
	{
		VALIDATE(CEntity::Initialise(IDB_ENEMY3_1SPRITE, IDB_ENEMY3_1MASK));
	}

	return (true);
}

void
CEnemy::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CEnemy::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void
CEnemy::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CEnemy::IsHit() const
{
	return (m_bHit);
}

int 
CEnemy::GetType()
{
	return(m_iType);
}

