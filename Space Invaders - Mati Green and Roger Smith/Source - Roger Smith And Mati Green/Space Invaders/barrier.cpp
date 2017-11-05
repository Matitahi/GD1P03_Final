//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: barrier.cpp
// Description	: Controls barrier implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "barrier.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBarrier::CBarrier()
	: m_bHit(false)
	, m_iHp(2)
{

}

CBarrier::~CBarrier()
{

}

bool 
CBarrier::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BARRIER1SPRITE, IDB_BARRIERMASK));

	return (true);
}

void 
CBarrier::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void 
CBarrier::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void 
CBarrier::SetHit(bool _b)
{
	m_bHit = _b;
}

bool 
CBarrier::IsHit() const
{
	return (m_bHit);
}

void 
CBarrier::ReduceHp()
{
	m_iHp--;

	if (m_iHp == 1)
	{
		CEntity::Initialise(IDB_BARRIER2SPRITE, IDB_BARRIERMASK);
	}
	else if (m_iHp == 0)
	{
		m_bHit = true;
	}
}

void CBarrier::SetHp(int _iHp)
{
	m_iHp = _iHp;

	switch (_iHp)
	{
		case 2:
		{
			CEntity::Initialise(IDB_BARRIER1SPRITE, IDB_BARRIERMASK);
		}

		case 1:
		{
			CEntity::Initialise(IDB_BARRIER2SPRITE, IDB_BARRIERMASK);
		}

		default:
		{
			m_bHit = true;
		}
	}
}
