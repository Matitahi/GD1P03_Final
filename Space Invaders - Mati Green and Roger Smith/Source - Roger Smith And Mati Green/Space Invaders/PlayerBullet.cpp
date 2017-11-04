//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: playerbullet.cpp
// Description	: Controls player bullet implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Includes
#include "PlayerBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayerBullet::CPlayerBullet()
: m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
, m_bHit(true)
{

}

CPlayerBullet::~CPlayerBullet()
{

}

bool
CPlayerBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
    VALIDATE(CEntity::Initialise(IDB_PLAYERBULLETSPRITE, IDB_PLAYERBULLETMASK));
    
    m_fX = _fPosX;
    m_fY = _fPosY;

    m_fVelocityX = _fVelocityX;
    m_fVelocityY = _fVelocityY;

    return (true);
}

void
CPlayerBullet::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CPlayerBullet::Process(float _fDeltaTick)
{
	

    //m_fX += m_fVelocityX * _fDeltaTick;
	if (!m_bHit)
	{
		m_fY += -(m_fVelocityY * _fDeltaTick);

		CEntity::Process(_fDeltaTick);
	}
}

float 
CPlayerBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
CPlayerBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CPlayerBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

void 
CPlayerBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

float 
CPlayerBullet::GetRadius() const
{
    return (GetWidth() / 2.0f);
}

void
CPlayerBullet::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CPlayerBullet::IsHit() const
{
	return (m_bHit);
}