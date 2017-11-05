//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: playership.cpp
// Description	: Controls player implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "gamesettings.h"

// This Include
#include "playership.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayerShip::CPlayerShip()
	: m_bHit(false)
{

}

CPlayerShip::~CPlayerShip()
{

}

bool
CPlayerShip::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PLAYERSHIPSPRITE, IDB_PLAYERSHIPMASK));

    return (true);
}

void
CPlayerShip::Draw()
{
    CEntity::Draw();
}

void
CPlayerShip::Process(float _fDeltaTick)
{
	CGameSettings& rGameSettings = CGameSettings::GetInstance();

	float fHalfPaddleW = m_pSprite->GetWidth() / 2.0;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += rGameSettings.GetPlayerSpeed() * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= rGameSettings.GetPlayerSpeed() * _fDeltaTick;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{

	}

	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPaddleW;
	}
	else if (m_fX + fHalfPaddleW >= 385)
	{
		m_fX = 385-fHalfPaddleW;
	}
	
	CEntity::Process(_fDeltaTick);
}

bool CPlayerShip::IsHit() const
{
	return false;
}
