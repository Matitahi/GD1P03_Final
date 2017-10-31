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

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes
#include "enemy.h"
#include "enemybullet.h"
#include "barrier.h"
#include "mysteryship.h"

// Types

// Constants

// Prototypes
class CPlayerBullet;
class CPlayerShip;
class CBrick;
class CFPSCounter;
class CBackGround;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPlayerShip* GetPlayerShip() const;

    int GetEnemiesRemaining() const;

protected:
	void ProcessPlayerCollision();
	void ProcessEnemyCollision();
	void ProcessEnemyShoot();
	void ProcessBulletBarrierCollisions();
	void ProcessBoundsCollisions();
	void ProcessMysteryShipSpawns();

	void ProcessCheckForLoss();
    void ProcessCheckForWin();

	void SetScore(int _iScore);
	int GetScore() const;

    void UpdateScoreText();
    void DrawScore();

	void DrawLives();

	void DrawFPS();

    void SetEnemiesRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CPlayerBullet* m_pPlayerBullet;
    CPlayerShip* m_pPlayerShip;
	CEnemy* m_pEnemies[11][5];
	std::vector<CBarrier*> m_vecBarrier;
    std::vector<CEnemyBullet*> m_vecEnemyBullets;
	CFPSCounter* m_fpsCounter;
	CMysteryShip* m_pMysteryShip;

    int m_iWidth;
    int m_iHeight;

    int m_iEnemiesRemaining;

	int m_iScore;
    std::string m_strScore;

	std::string m_strLives;
};

#endif    // __LEVEL_H__
