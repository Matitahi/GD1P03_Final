//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: enemybullet.cpp
// Description	: Controls enemy bullet implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "gamesettings.h"

// This Includes
#include "enemybullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEnemyBullet::CEnemyBullet()
	: m_fVelocityY(0.0f)
	, m_bHit(false)
{

}

CEnemyBullet::~CEnemyBullet()
{

}

bool 
CEnemyBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityY)
{
	VALIDATE(CEntity::Initialise(IDB_ENEMYBULLETSPRITE, IDB_ENEMYBULLETMASK));

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityY = _fVelocityY;

	return (true);
}

void 
CEnemyBullet::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}	
}

void 
CEnemyBullet::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		m_fY += (m_fVelocityY * _fDeltaTick);
		CEntity::Process(_fDeltaTick);
	}
}

float 
CEnemyBullet::GetVelocityY() const
{
	return (m_fVelocityY);
}

void 
CEnemyBullet::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

float 
CEnemyBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}

void CEnemyBullet::SetHit(bool _bHit)
{
	m_bHit = _bHit;
}

bool CEnemyBullet::IsHit() const
{
	return m_bHit;
}

