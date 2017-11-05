//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: game.cpp
// Description	: Controls game implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"

// This Include
#include "gamesettings.h"

// Static Variables
CGameSettings* CGameSettings::s_pGameSettings = 0;

// Static Function Prototypes

// Implementation

CGameSettings::CGameSettings()
	: m_fPlayerSpeed(400.0)
	, m_fPlayerBulletSpeed(250.0)
	, m_iPlayerLives(3)
	, m_fAlienSpeed(50.0)
	, m_fAlienType1BulletSpeed(75.0)
	, m_fAlienType2BulletSpeed(100.0)
	, m_fAlienType3BulletSpeed(125.0)
	, m_iAlienQuantity(55)
	, m_fMysteryShipSpeed(100.0)
{
}

CGameSettings::~CGameSettings()
{
}

float
CGameSettings::GetPlayerSpeed() const
{
	return (m_fPlayerSpeed);
}

void
CGameSettings::SetPlayerSpeed(int _iIndex)
{
	m_fPlayerSpeed = (_iIndex * 100) + 100;
}

float
CGameSettings::GetPlayerBulletSpeed() const
{
	return (m_fPlayerBulletSpeed);
}

void CGameSettings::SetPlayerBulletSpeed(int _iIndex)
{
	m_fPlayerBulletSpeed = (_iIndex * 50) + 50;
}

int
CGameSettings::GetPlayerLives() const
{
	return (m_iPlayerLives);
}

void CGameSettings::SetPlayerLives(int _iIndex)
{
	m_iPlayerLives = _iIndex;
}

float
CGameSettings::GetAlienSpeed() const
{
	return (m_fAlienSpeed);
}

void CGameSettings::SetAlienSpeed(int _iIndex)
{
	m_fAlienSpeed = (_iIndex * 10) + 10;
}

float CGameSettings::GetAlienType1BulletSpeed() const
{
	return (m_fAlienType1BulletSpeed);
}

void CGameSettings::SetAlienType1BulletSpeed(int _iIndex)
{
	m_fAlienType1BulletSpeed = (_iIndex * 25) + 25;
}

float CGameSettings::GetAlienType2BulletSpeed() const
{
	return (m_fAlienType2BulletSpeed);
}

void CGameSettings::SetAlienType2BulletSpeed(int _iIndex)
{
	m_fAlienType2BulletSpeed = (_iIndex * 25) + 25;
}

float CGameSettings::GetAlienType3BulletSpeed() const
{
	return (m_fAlienType3BulletSpeed);
}

void CGameSettings::SetAlienType3BulletSpeed(int _iIndex)
{
	m_fAlienType3BulletSpeed = (_iIndex * 25) + 25;
}

int
CGameSettings::GetAlienQuantity() const
{
	return (m_iAlienQuantity);
}

void CGameSettings::SetAlienQuantity(int _iIndex)
{
	m_iAlienQuantity = (_iIndex * 10) + 1;
}

float
CGameSettings::GetMysteryShipSpeed() const
{
	return (m_fMysteryShipSpeed);
}

void CGameSettings::SetMysteryShipSpeed(int _iIndex)
{
	m_fMysteryShipSpeed = (_iIndex * 25) + 25;
}

TCHAR*
CGameSettings::GetPlayerSpeedText(int _iIndex)
{
	return m_pcPlayerSpeed[_iIndex];
}

TCHAR*
CGameSettings::GetPlayerBulletSpeedText(int _iIndex) const
{
	return (m_pcPlayerBulletSpeed[_iIndex]);
}

TCHAR*
CGameSettings::GetPlayerLivesText(int _iIndex) const
{
	return (m_pcPlayerLives[_iIndex]);
}

TCHAR*
CGameSettings::GetAlienSpeedText(int _iIndex) const
{
	return (m_pcAlienSpeed[_iIndex]);
}

TCHAR*
CGameSettings::GetAlienBulletSpeedText(int _iIndex) const
{
	return (m_pcAlienBulletSpeed[_iIndex]);
}

TCHAR*
CGameSettings::GetAlienQuantityText(int _iIndex) const
{
	return (m_pcAlienQuantity[_iIndex]);
}

TCHAR*
CGameSettings::GetMysteryShipSpeedText(int _iIndex) const
{
	return (m_pcMysteryShipSpeed[_iIndex]);
}

CGameSettings & CGameSettings::GetInstance()
{
	if (s_pGameSettings == 0)
	{
		s_pGameSettings = new CGameSettings();
	}

	return (*s_pGameSettings);
}

void CGameSettings::DestroyInstance()
{
	delete s_pGameSettings;
	s_pGameSettings = 0;
}