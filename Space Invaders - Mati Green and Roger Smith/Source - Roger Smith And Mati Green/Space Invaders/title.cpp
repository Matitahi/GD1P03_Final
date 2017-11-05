//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: title.cpp
// Description	: Controls title screen implementation logic
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
#include "title.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTitle::CTitle()
	: m_iWidth(0)
	, m_iHeight(0)
{
}


CTitle::~CTitle()
{
	delete m_pBackground;
	m_pBackground = 0;
}

bool CTitle::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());

	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	return (true);
}

void CTitle::Draw()
{
	m_pBackground->Draw();
	// Function here to write text and images to the screen
	DrawMenu();
}

void CTitle::Process(float _fDeltaTick)
{
	// Process background.
	m_pBackground->Process(_fDeltaTick);

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		CGame& rGame = CGame::GetInstance();
		rGame.SetGameState(INGAME);
	}
}

void CTitle::DrawMenu()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	int kiX = m_iWidth / 2;
	int kiY = 30;
	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER);

	const char* output[] = { "PLAY", "SPACE INVADERS", "*SCORE ADVANCE TABLE*", "= ? MYSTERY", "= 30 POINTS", "= 20 POINTS", "= 10 POINTS", "PUSH DOWN ARROW TO BEGIN"};
	
	for (int i = 0; i < 8; ++i)
	{
		TextOutA(hdc, kiX, kiY, output[i], strlen(output[i]));
		kiY += 30;
	}

	SetTextAlign(hdc, TA_LEFT);
}
