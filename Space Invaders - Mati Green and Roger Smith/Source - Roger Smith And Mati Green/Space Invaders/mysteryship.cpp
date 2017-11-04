//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: mysteryship.cpp
// Description	: Controls mystery ship implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "mysteryship.h"

CMysteryShip::CMysteryShip()
	: m_fVelocityX(0.0f)
	, m_bHit(true)
{

}

CMysteryShip::~CMysteryShip()
{

}

bool
CMysteryShip::Initialise(float _fPosX, float _fPosY, float _fVelocityX)
{
	VALIDATE(CEntity::Initialise(IDB_ENEMY4SPRITE, IDB_ENEMY4MASK));

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityX = _fVelocityX;

	return (true);
}

void
CMysteryShip::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CMysteryShip::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		m_fX += (m_fVelocityX * _fDeltaTick);

		CEntity::Process(_fDeltaTick);
	}
}

void
CMysteryShip::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CMysteryShip::IsHit() const
{
	return(m_bHit);
}

void
CMysteryShip::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}
