//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: level.cpp
// Description	: Controls level implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz
//

// Library Includes
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Local Includes
#include "Game.h"
#include "gamesettings.h"
#include "playership.h"
#include "PlayerBullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CGameSettings& g_rGameSettings = CGameSettings::GetInstance();

enum EShipPoints
{
	POINTS_ENEMY1 = 10,
	POINTS_ENEMY2 = 20,
	POINTS_ENEMY3 = 30,
};

CLevel::CLevel()
: m_iEnemiesRemaining(0)
, m_pPlayerShip(0)
, m_pPlayerBullet(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
, m_iScore(0)
, m_iType1BulletSpeedIndex(2)
, m_iType2BulletSpeedIndex(3)
, m_iType3BulletSpeedIndex(4)
{
}

CLevel::~CLevel()
{
    delete m_pPlayerShip;
    m_pPlayerShip = 0;

    delete m_pPlayerBullet;
    m_pPlayerBullet = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;
}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

	srand(time(NULL));

    const float fPlayerBulletVelX = 0.0f;

	CGameSettings& rGameSettings = CGameSettings::GetInstance();

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());

	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	m_pPlayerBullet = new CPlayerBullet();
    VALIDATE(m_pPlayerBullet->Initialise(0, 0, fPlayerBulletVelX, rGameSettings.GetPlayerBulletSpeed()));

    m_pPlayerShip = new CPlayerShip();
    VALIDATE(m_pPlayerShip->Initialise());

	m_pMysteryShip = new CMysteryShip();
	VALIDATE(m_pMysteryShip->Initialise(-10, 10, rGameSettings.GetMysteryShipSpeed()));

    // Set the player ship's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pPlayerShip->SetX(_iWidth / 2.0f);
    m_pPlayerShip->SetY(_iHeight - ( 1.2 * m_pPlayerShip->GetHeight()));

    const int kiStartX = 20;
    const int kiGap = 5;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

	// Creates the barriers.
	ImplementBarriers();

	// Creates the enemies.
	int iEnemyType = 3;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			CEnemy* pEnemy = new CEnemy(iEnemyType, g_rGameSettings.GetAlienSpeed());
			VALIDATE(pEnemy->Initialise());

			pEnemy->SetX(static_cast<float>(iCurrentX));
			pEnemy->SetY(static_cast<float>(iCurrentY));

			iCurrentX += 24 + kiGap;

			m_pEnemies[j][i] = pEnemy;
		}

		iCurrentX = kiStartX;
		iCurrentY += 20;

		if ((i == 0) || (i == 2))
		{
			iEnemyType--;
		}
	}

    SetEnemiesRemaining(rGameSettings.GetAlienQuantity());

	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	SetTextColor(CGame::GetInstance().GetBackBuffer()->GetBFDC(), 0x00FFFFFF);

    return (true);
}

void
CLevel::Draw()
{
	// Draw Background.
	m_pBackground->Draw();

	// Draw enemies.
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			m_pEnemies[j][i]->Draw();
		}
	}

	// Draw enemy bullets.
	for (int i = 0; i < m_vecEnemyBullets.size(); ++i)
	{
		m_vecEnemyBullets[i]->Draw();
	}

	// Draw barriers.
	for (int i = 0; i < m_vecBarrier.size(); ++i)
	{
		m_vecBarrier[i]->Draw();
	}

	// Draw player ship.
    m_pPlayerShip->Draw();

	// Draw player bullet.
    m_pPlayerBullet->Draw();

	// Draw Mystery ship.
	m_pMysteryShip->Draw();

	// Draw score.
    DrawScore();

	// Draw number of lives the player has remaining.
	DrawLives();

	// DrawFPS
	//DrawFPSText();
}

void
CLevel::Process(float _fDeltaTick)
{
	// Process background.
	m_pBackground->Process(_fDeltaTick);

	// Process player bullet.
	m_pPlayerBullet->Process(_fDeltaTick);

	// Process player ship.
	m_pPlayerShip->Process(_fDeltaTick);

	// Process mystery ship.
	m_pMysteryShip->Process(_fDeltaTick);

	// Process player collisions with enemy or enemy bullet.
	ProcessPlayerCollision();
	
	// Process player bullet collisions with enemies.
    ProcessEnemyCollision();

	// Process enemy shooting.
	ProcessEnemyShoot();

	// Process enemy and player bullet collisions with barriers.
	ProcessBulletBarrierCollisions();

	// Process entity collisions with window bounds.
	ProcessBoundsCollisions();

	// Process checking for loss condition.
	ProcessCheckForLoss();

	// Process checking for win condition.
    ProcessCheckForWin();

	// Process the spawning of the mystery ship.
	ProcessMysteryShipSpawns();
	
	// Process barriers.
	for (int i = 0; i < m_vecBarrier.size(); ++i)
	{
		m_vecBarrier[i]->Process(_fDeltaTick);
	}

	// Process enemies.
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			m_pEnemies[j][i]->Process(_fDeltaTick);
		}
	}

	// Process enemy bullets.
	for (int i = 0; i < m_vecEnemyBullets.size(); ++i)
	{
		m_vecEnemyBullets[i]->Process(_fDeltaTick);
	}

	// Process player ship shooting.
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_pPlayerBullet->IsHit() == true)
		{
			m_pPlayerBullet->SetX(m_pPlayerShip->GetX());
			m_pPlayerBullet->SetY(m_pPlayerShip->GetY());
			m_pPlayerBullet->SetHit(false);
		}
	}
    
	// Process fps counter.
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPlayerShip* 
CLevel::GetPlayerShip() const
{
    return (m_pPlayerShip);
}

void 
CLevel::ProcessBulletBarrierCollisions()
{
	// Enemy Bullet Collisions with barrier

	// for each barrier.
	for (int j = 0; j < m_vecBarrier.size(); ++j)
	{
		// for each enemy bullet.
		for (int i = 0; i < m_vecEnemyBullets.size(); ++i)
		{
			// if the barrier is not yet hit.
			if (m_vecBarrier[j]->IsHit() == false)
			{
				// Get 
				float fBulletX = m_vecEnemyBullets[i]->GetX();
				float fBulletY = m_vecEnemyBullets[i]->GetY();

				float fBulletH = m_vecEnemyBullets[i]->GetHeight();
				float fBulletW = m_vecEnemyBullets[i]->GetWidth();

				float fBarrierX = m_vecBarrier[j]->GetX();
				float fBarrierY = m_vecBarrier[j]->GetY();

				float fBarrierH = m_vecBarrier[j]->GetHeight();
				float fBarrierW = m_vecBarrier[j]->GetWidth();

				if ((fBulletX + fBulletW > fBarrierX - fBarrierW / 2) && //ball.right > paddle.left
					(fBulletX - fBulletW < fBarrierX + fBarrierW / 2) && //ball.left < paddle.right
					(fBulletY + fBulletH > fBarrierY - fBarrierH / 2) && //ball.bottom > paddle.top
					(fBulletY - fBulletH < fBarrierY + fBarrierH / 2))  //ball.top < paddle.bottom
				{
					m_vecBarrier[j]->ReduceHp();
					delete m_vecEnemyBullets[i];
					m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + i);
				}
			}
		}
	}

	// Player Bullet Collisions with barrier
	for (int i = 0; i < m_vecBarrier.size(); ++i)
	{
		if ((m_vecBarrier[i]->IsHit() == false) && (m_pPlayerBullet->IsHit() == false))
		{
			float fBarrierX = m_vecBarrier[i]->GetX();
			float fBarrierY = m_vecBarrier[i]->GetY();

			float fBarrierH = m_vecBarrier[i]->GetHeight();
			float fBarrierW = m_vecBarrier[i]->GetWidth();

			float fBulletX = m_pPlayerBullet->GetX();
			float fBulletY = m_pPlayerBullet->GetY();

			float fBulletH = m_pPlayerBullet->GetHeight();
			float fBulletW = m_pPlayerBullet->GetWidth();

			if ((fBulletX + fBulletW > fBarrierX - fBarrierW / 2) && //ball.right > paddle.left
				(fBulletX - fBulletW < fBarrierX + fBarrierW / 2) && //ball.left < paddle.right
				(fBulletY + fBulletH > fBarrierY - fBarrierH / 2) && //ball.bottom > paddle.top
				(fBulletY - fBulletH < fBarrierY + fBarrierH / 2))  //ball.top < paddle.bottom
			{
				m_pPlayerBullet->SetHit(true);
				m_vecBarrier[i]->ReduceHp();
			}
		}
	}
}

void
CLevel::ProcessBoundsCollisions()
{
	// Enemy Bullet out of bounds.
	for (int i = 0; i < m_vecEnemyBullets.size(); ++i)
	{
		if (m_vecEnemyBullets[i]->GetY() > m_iHeight)
		{
			delete m_vecEnemyBullets[i];
			m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + i);
		}
	}

	// Player Bullet out of bounds.
	if (m_pPlayerBullet->GetY() < 0)
	{
		m_pPlayerBullet->SetHit(true);
	}

	// MysteryShip out of bounds.
	if (m_pMysteryShip->GetX() > (m_iWidth + (m_pMysteryShip->GetWidth() / 2)))
	{
		m_pMysteryShip->SetHit(true);
	}

	// enemy out of bounds.
	int iLeftBound = m_pEnemies[0][0]->GetWidth();
	int iRightBound = m_iWidth - m_pEnemies[0][0]->GetWidth();
	int iDeltaY = 0;
	//bool bCanChangeDirection = true;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (((m_pEnemies[j][i]->GetX() >= iRightBound) || (m_pEnemies[j][i]->GetX() <= iLeftBound)))
			{
				//bCanChangeDirection = false;
				for (int k = 0; k < 5; ++k)
				{
					for (int l = 0; l < 11; ++l)
					{
						if (m_pEnemies[l][k]->MovingRight())
						{
							m_pEnemies[l][k]->SetX(m_pEnemies[l][k]->GetX() - 0.5);
						}
						else
						{
							m_pEnemies[l][k]->SetX(m_pEnemies[l][k]->GetX() + 0.5);
						}

						//m_pEnemies[l][k]->CanMove(false);
						m_pEnemies[l][k]->ChangeDirection();
						iDeltaY = m_pEnemies[l][k]->GetY() + (m_pEnemies[l][k]->GetHeight() * 0.2);
						m_pEnemies[l][k]->SetY(iDeltaY);
					}
				}
			}
		}
	}
}

void 
CLevel::ProcessEnemyShoot()
{
	CGameSettings& rGameSettings = CGameSettings::GetInstance();
	bool bCanShoot = true;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (m_pEnemies[j][i]->IsHit() == false)
			{
				if (i < 4)
				{
					if (m_pEnemies[j][i+1]->IsHit() == false)
					{
						bCanShoot = false;
					}
				}

				if (bCanShoot == true)
				{
					if (m_pEnemies[j][i]->GetType() == 1)
					{
						if ((rand() % 10000 + 1) == 1)
						{

							CEnemyBullet* pEnemyBullet = new CEnemyBullet();
							pEnemyBullet->Initialise(m_pEnemies[j][i]->GetX(), m_pEnemies[j][i]->GetY(), rGameSettings.GetAlienType1BulletSpeed());
							m_vecEnemyBullets.push_back(pEnemyBullet);

						}
					}
					else if (m_pEnemies[j][i]->GetType() == 2)
					{
						if ((rand() % 7500 + 1) == 1)
						{
							CEnemyBullet* pEnemyBullet = new CEnemyBullet();
							pEnemyBullet->Initialise(m_pEnemies[j][i]->GetX(), m_pEnemies[j][i]->GetY(), rGameSettings.GetAlienType2BulletSpeed());
							m_vecEnemyBullets.push_back(pEnemyBullet);
						}
					}
					else
					{
						if ((rand() % 5000 + 1) == 1)
						{
							CEnemyBullet* pEnemyBullet = new CEnemyBullet();
							pEnemyBullet->Initialise(m_pEnemies[j][i]->GetX(), m_pEnemies[j][i]->GetY(), rGameSettings.GetAlienType3BulletSpeed());
							m_vecEnemyBullets.push_back(pEnemyBullet);
						}
					}
				}
			}
			bCanShoot = true;
		}
	}
}

void 
CLevel::ProcessMysteryShipSpawns()
{
	if (m_pMysteryShip->IsHit() == true)
	{
		if ((rand() % 10000 + 1) == 1)
		{
			m_pMysteryShip->SetX(0 - (m_pMysteryShip->GetWidth() / 2));
			m_pMysteryShip->SetY(10);
			// Possibly process before drawn?
			m_pMysteryShip->SetHit(false);
		}
	}
}

CPlayerBullet * CLevel::GetPlayerBullet() const
{
	return (m_pPlayerBullet);
}

void CLevel::ImplementBarriers()
{
	int iIndex = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 6; ++k)
			{
				if (!((k == 0 && j == 0) || (k == 5 && j == 0)
					|| (k == 2 && j == 2) || (k == 3 && j == 2)))
				{
					iIndex = i + j + k;
					//if (m_vecBarrier[iIndex] != 0)
					//{
					//	delete m_vecBarrier[iIndex];
					//	m_vecBarrier[iIndex] = NULL;
					//}

					CBarrier* pBarrier = new CBarrier();
					pBarrier->Initialise();

					pBarrier->SetX(20 + (10 * k) + (95 * i) + (1 * k));
					pBarrier->SetY(270 + (10 * j) + (1 * j));

					m_vecBarrier.push_back(pBarrier);
				}
			}
		}
	}
}

void
CLevel::RestoreBarriers()
{
	std::vector<CBarrier*>::const_iterator it = m_vecBarrier.begin();
	while (it != m_vecBarrier.end())
	{
		if ((*it)->IsHit() == true)
		{
			(*it)->SetHit(false);
		}

		(*it)->SetHp(2);

		it++;
	}
}

void CLevel::ProcessPlayerCollision()
{
	bool bPlayerHit = false;

	for (int i = 0; i < m_vecEnemyBullets.size(); ++i)
	{
		float fEnemyBulletH = m_vecEnemyBullets[i]->GetHeight();
		float fEnemyBulletW = m_vecEnemyBullets[i]->GetWidth();

		float fEnemyBulletX = m_vecEnemyBullets[i]->GetX();
		float fEnemyBulletY = m_vecEnemyBullets[i]->GetY();

		float fPlayerX = m_pPlayerShip->GetX();
		float fPlayerY = m_pPlayerShip->GetY();

		float fPlayerH = m_pPlayerShip->GetHeight();
		float fPlayerW = m_pPlayerShip->GetWidth();

		if ((fEnemyBulletX + fEnemyBulletW > fPlayerX - fPlayerW / 2) && //ball.right > paddle.left
			(fEnemyBulletX - fEnemyBulletW < fPlayerX + fPlayerW / 2) && //ball.left < paddle.right
			(fEnemyBulletY + fEnemyBulletH > fPlayerY - fPlayerH / 2) && //ball.bottom > paddle.top
			(fEnemyBulletY - fEnemyBulletH < fPlayerY + fPlayerH / 2))  //ball.top < paddle.bottom
		{
			delete m_vecEnemyBullets[i];
			m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + i);
			bPlayerHit = true;
		}
	}

	if (bPlayerHit == true)
	{
		g_rGameSettings.SetPlayerLives(g_rGameSettings.GetPlayerLives() - 1);
	}
}

void
CLevel::ProcessEnemyCollision()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if ((!m_pEnemies[j][i]->IsHit()) && (!m_pPlayerBullet->IsHit()))
			{
				float fPlayerBulletH = m_pPlayerBullet->GetHeight();
				float fPlayerBulletW = m_pPlayerBullet->GetWidth();

				float fPlayerBulletX = m_pPlayerBullet->GetX();
				float fPlayerBulletY = m_pPlayerBullet->GetY();

				float fEnemyX = m_pEnemies[j][i]->GetX();
				float fEnemyY = m_pEnemies[j][i]->GetY();

				float fEnemyH = m_pEnemies[j][i]->GetHeight();
				float fEnemyW = m_pEnemies[j][i]->GetWidth();

				if ((fPlayerBulletX + fPlayerBulletW > fEnemyX - fEnemyW / 2) && //ball.right > paddle.left
					(fPlayerBulletX - fPlayerBulletW < fEnemyX + fEnemyW / 2) && //ball.left < paddle.right
					(fPlayerBulletY + fPlayerBulletH > fEnemyY - fEnemyH / 2) && //ball.bottom > paddle.top
					(fPlayerBulletY - fPlayerBulletH < fEnemyY + fEnemyH / 2))  //ball.top < paddle.bottom
				{
					m_pPlayerBullet->SetHit(true);
					m_pEnemies[j][i]->SetHit(true);

					SetEnemiesRemaining(GetEnemiesRemaining() - 1);

					// Find the type of enemy that was hit and store the appropriate amount of points
					int iDeltaScore = 0;
					switch (m_pEnemies[j][i]->GetType())
					{
					case 1:
					{
						iDeltaScore = POINTS_ENEMY1;
						break;
					}

					case 2:
					{
						iDeltaScore = POINTS_ENEMY2;
						break;
					}

					case 3:
					{
						iDeltaScore = POINTS_ENEMY3;
						break;
					}

					default:break;
					}

					// Add the points above to the player's total score
					SetScore(GetScore() + iDeltaScore);
					UpdateScoreText();
				}
			}
		}
    }

	if ((m_pMysteryShip->IsHit() == false) && (m_pPlayerBullet->IsHit() == false))
	{
		float fMysteryShipX = m_pMysteryShip->GetX();
		float fMysteryShipY = m_pMysteryShip->GetY();

		float fMysteryShipH = m_pMysteryShip->GetHeight();
		float fMysteryShipW = m_pMysteryShip->GetWidth();

		float fBulletX = m_pPlayerBullet->GetX();
		float fBulletY = m_pPlayerBullet->GetY();

		float fBulletH = m_pPlayerBullet->GetHeight();
		float fBulletW = m_pPlayerBullet->GetWidth();

		if ((fBulletX + fBulletW > fMysteryShipX - fMysteryShipW / 2) && //ball.right > paddle.left
			(fBulletX - fBulletW < fMysteryShipX + fMysteryShipW / 2) && //ball.left < paddle.right
			(fBulletY + fBulletH > fMysteryShipY - fMysteryShipH / 2) && //ball.bottom > paddle.top
			(fBulletY - fBulletH < fMysteryShipY + fMysteryShipH / 2))  //ball.top < paddle.bottom
		{
			m_pPlayerBullet->SetHit(true);
			m_pMysteryShip->SetHit(true);

			// Since mystery ship has a variety of possible options, easier to deal with through random numbers
			int iRand = rand() % 6 + 1;
			int iDeltaScore = iRand * 50;
			
			// Add the points above to the player's total score
			SetScore(GetScore() + iDeltaScore);
			UpdateScoreText();
		}
	}

}

void CLevel::ProcessCheckForLoss()
{
	if (g_rGameSettings.GetPlayerLives() == 0)
	{
		CGame::GetInstance().GameOverLost();
	}
}

void
CLevel::ProcessCheckForWin()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (m_pEnemies[j][i]->IsHit() == false)
			{
				return;
			}
		}
	}

    CGame::GetInstance().GameOverWon();
}

void CLevel::SetScore(int _iScore)
{
	m_iScore = _iScore;
}

int CLevel::GetScore() const
{
	return m_iScore;
}

int 
CLevel::GetEnemiesRemaining() const
{
    return (m_iEnemiesRemaining);
}

void 
CLevel::SetEnemiesRemaining(int _i)
{
    m_iEnemiesRemaining = _i;
    UpdateScoreText();
}

void
CLevel::UpdateScoreText()
{
	m_strScore = "Score: ";

	m_strScore += ToString(GetScore());
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void
CLevel::DrawLives()
{
	m_strLives = "Lives: ";

	m_strLives += ToString(g_rGameSettings.GetPlayerLives());
	
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = m_iWidth - 75;
	const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, m_strLives.c_str(), static_cast<int>(m_strLives.size()));
}

void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}