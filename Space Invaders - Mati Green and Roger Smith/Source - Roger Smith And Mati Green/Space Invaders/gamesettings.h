//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: gamesettings.h
// Description	: Game settings declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

#pragma once

#if !defined(__GAMESETTINGS_H__)
#define __GAMESETTINGS_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "clock.h"

// Types

// Constants

// Prototypes

class CGameSettings
{
public:
	CGameSettings();
	~CGameSettings();

	float GetPlayerSpeed() const;
	void SetPlayerSpeed(int _iIndex);

	float GetPlayerBulletSpeed() const;
	void SetPlayerBulletSpeed(int _iIndex);

	int GetPlayerLives() const;
	void SetPlayerLives(int _iIndex);

	float GetAlienSpeed() const;
	void SetAlienSpeed(int _iIndex);

	float GetAlienType1BulletSpeed() const;
	void SetAlienType1BulletSpeed(int _iIndex);

	float GetAlienType2BulletSpeed() const;
	void SetAlienType2BulletSpeed(int _iIndex);

	float GetAlienType3BulletSpeed() const;
	void SetAlienType3BulletSpeed(int _iIndex);

	int GetAlienQuantity() const;
	void SetAlienQuantity(int _iIndex);
	
	float GetMysteryShipSpeed() const;
	void SetMysteryShipSpeed(int _iIndex);

	TCHAR* GetPlayerSpeedText(int _iIndex);
	TCHAR* GetPlayerBulletSpeedText(int _iIndex) const;
	TCHAR* GetPlayerLivesText(int _iIndex) const;
	TCHAR* GetAlienSpeedText(int _iIndex) const;
	TCHAR* GetAlienBulletSpeedText(int _iIndex) const;
	TCHAR* GetAlienQuantityText(int _iIndex) const;
	TCHAR* GetMysteryShipSpeedText(int _iIndex) const;

	// Singleton Methods
	static CGameSettings& GetInstance();
	static void DestroyInstance();

protected:
private:

public:
protected:
	float m_fPlayerSpeed;
	float m_fPlayerBulletSpeed;
	int m_iPlayerLives;
	float m_fAlienSpeed;
	float m_fAlienType1BulletSpeed;
	float m_fAlienType2BulletSpeed;
	float m_fAlienType3BulletSpeed;
	int m_iAlienQuantity;
	float m_fMysteryShipSpeed;

	TCHAR* m_pcPlayerSpeed[6] = { TEXT("100"), TEXT("200"), TEXT("300"), TEXT("400"), TEXT("500"), TEXT("600") };
	TCHAR* m_pcPlayerBulletSpeed[5] = { TEXT("50"), TEXT("100"), TEXT("150"), TEXT("200"), TEXT("250") };
	TCHAR* m_pcPlayerLives[6] = { TEXT("0"), TEXT("1"), TEXT("2"), TEXT("3"), TEXT("4"), TEXT("5") };
	TCHAR* m_pcAlienSpeed[5] = { TEXT("10"), TEXT("20"), TEXT("30"), TEXT("40"), TEXT("50") };
	TCHAR* m_pcAlienBulletSpeed[5] = { TEXT("25"), TEXT("50"), TEXT("75"), TEXT("100"), TEXT("125") };
	TCHAR* m_pcAlienQuantity[6] = { TEXT("1"), TEXT("11 (one row)"), TEXT("22 (two rows)"),
		TEXT("33 (three rows)"), TEXT("44 (four rows)"), TEXT("55 (five rows)") };
	TCHAR* m_pcMysteryShipSpeed[5] = { TEXT("25"), TEXT("50"), TEXT("75"), TEXT("100"), TEXT("125")};

	// Singleton Instance
	static CGameSettings* s_pGameSettings;
private:

};

#endif //__GAMESETTINGS_H__
