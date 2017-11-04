//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: enemy.cpp
// Description	: Controls enemy implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

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
	, m_bMoveRight(true)
	, m_iStepTick(0)
	, m_iStepFreq(2)
	, m_fSpeed(50.0)
	, m_bCanMove(true)
{
	m_iType = _iType;
}

CEnemy::CEnemy()
	: m_bHit(false)
	, m_bMoveRight(true)
	, m_iStepTick(0)
	, m_iStepFreq(2)
	, m_fSpeed(50.0)
	, m_bCanMove(true)
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
	bool bCanStep = m_iStepTick % 20 == 0;
	if (!m_bHit && m_bCanMove && bCanStep)
	{
		if (m_bMoveRight)
		{
			m_fX += m_fSpeed * _fDeltaTick;
		}
		else
		{
			m_fX -= m_fSpeed * _fDeltaTick;
		}
		CEntity::Process(_fDeltaTick);
	}
	m_iStepTick++;
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

void CEnemy::ChangeDirection() 
{
	if (m_bMoveRight == true)
	{
		m_bMoveRight = false;
	}
	else
	{
		m_bMoveRight = true;
		m_fSpeed += 2.5;
	}
}

bool CEnemy::MovingRight() const
{
	return m_bMoveRight;
}

void CEnemy::CanMove(bool _bMovement)
{
	m_bCanMove = _bMovement;
}

int 
CEnemy::GetType()
{
	return(m_iType);
}

