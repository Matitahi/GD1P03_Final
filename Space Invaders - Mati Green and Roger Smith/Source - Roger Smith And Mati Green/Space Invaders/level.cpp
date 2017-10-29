//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Local Includes
#include "Game.h"
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

CLevel::CLevel()
: m_iEnemiesRemaining(0)
, m_pPlayerShip(0)
, m_pPlayerBullet(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
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

    const float fBallVelX = 0.0f;
    const float fBallVelY = 230.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	m_pPlayerBullet = new CPlayerBullet();
    VALIDATE(m_pPlayerBullet->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, fBallVelX, fBallVelY));

    m_pPlayerShip = new CPlayerShip();
    VALIDATE(m_pPlayerShip->Initialise());

    // Set the player ship's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pPlayerShip->SetX(_iWidth / 2.0f);
    m_pPlayerShip->SetY(_iHeight - ( 1.2 * m_pPlayerShip->GetHeight()));

    const int kiNumEnemies = 55;
    const int kiStartX = 20;
    const int kiGap = 5;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

	// Creates the barriers.
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 6; ++k)
			{
				if (!((k == 0 && j == 0) || (k == 5 && j == 0)
					|| (k == 2 && j == 2) || (k == 3 && j == 2)))
				{
					CBarrier* pBarrier = new CBarrier();
					VALIDATE(pBarrier->Initialise());

					pBarrier->SetX(20 + (10 * k) + (95 * i) + (1 * k));
					pBarrier->SetY(270 + (10 * j) + (1 * j));

					m_vecBarrier.push_back(pBarrier);
				}
			}
		}
	}

	// Creates the enemies.
	int iEnemyType = 3;

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			CEnemy* pEnemy = new CEnemy(iEnemyType);
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

    SetEnemiesRemaining(kiNumEnemies);

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

	// Draw score.
    DrawScore();

	// Draw fps.
	DrawFPS();
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

	// Process player bullet collisions with enemies.
    ProcessEnemyCollision();

	// Process enemy shooting.
	ProcessEnemyShoot();

	// Process enemy and player bullet collisions with barriers.
	ProcessBulletBarrierCollisions();

	// Process entity collisions with window bounds.
	ProcessBoundsCollisions();

	// Process checking for win condition.
    ProcessCheckForWin();
	
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

	// enemy out of bounds.
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if ((m_pEnemies[j][i]->GetX() > m_iWidth)
				|| (m_pEnemies[j][i]->GetX() < 0))
			{
				// do logic.
			}
		}
	}
}

void 
CLevel::ProcessEnemyShoot()
{
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
							pEnemyBullet->Initialise(m_pEnemies[j][i]->GetX(), m_pEnemies[j][i]->GetY(), 75.0f);
							m_vecEnemyBullets.push_back(pEnemyBullet);

						}
					}
					else if (m_pEnemies[j][i]->GetType() == 2)
					{
						if ((rand() % 7500 + 1) == 1)
						{
							CEnemyBullet* pEnemyBullet = new CEnemyBullet();
							pEnemyBullet->Initialise(m_pEnemies[j][i]->GetX(), m_pEnemies[j][i]->GetY(), 100.0f);
							m_vecEnemyBullets.push_back(pEnemyBullet);
						}
					}
					else
					{
						if ((rand() % 5000 + 1) == 1)
						{
							CEnemyBullet* pEnemyBullet = new CEnemyBullet();
							pEnemyBullet->Initialise(m_pEnemies[j][i]->GetX(), m_pEnemies[j][i]->GetY(), 125.0f);
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
CLevel::ProcessEnemyCollision()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (!m_pEnemies[j][i]->IsHit())
			{
				float fBallR = m_pPlayerBullet->GetRadius();

				float fBallX = m_pPlayerBullet->GetX();
				float fBallY = m_pPlayerBullet->GetY();

				float fEnemyX = m_pEnemies[j][i]->GetX();
				float fEnemyY = m_pEnemies[j][i]->GetY();

				float fEnemyH = m_pEnemies[j][i]->GetHeight();
				float fEnemyW = m_pEnemies[j][i]->GetWidth();

				if ((fBallX + fBallR > fEnemyX - fEnemyW / 2) &&
					(fBallX - fBallR < fEnemyX + fEnemyW / 2) &&
					(fBallY + fBallR > fEnemyY - fEnemyH / 2) &&
					(fBallY - fBallR < fEnemyY + fEnemyH / 2))
				{
					m_pPlayerBullet->SetHit(true);
					m_pEnemies[j][i]->SetHit(true);

					SetEnemiesRemaining(GetEnemiesRemaining() - 1);
				}
			}
		}
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
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
CLevel::UpdateScoreText()
{
    m_strScore = "Enemies Remaining: ";

    m_strScore += ToString(GetEnemiesRemaining());
}


void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}
