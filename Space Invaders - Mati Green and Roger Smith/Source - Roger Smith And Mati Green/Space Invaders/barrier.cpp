//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
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