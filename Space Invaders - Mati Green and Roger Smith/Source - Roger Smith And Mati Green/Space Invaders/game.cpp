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
#include <fstream>
#include <tchar.h>

// Local Includes
#include "Clock.h"
#include "title.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
	: m_pLevel(0)
	, m_pTitle(0)
	, m_pGameover(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
	, m_eGameState(TITLE)
{
}

CGame::~CGame()
{
	delete m_pTitle;
	m_pTitle = 0;

	delete m_pLevel;
	m_pLevel = 0;

	delete m_pGameover;
	m_pGameover = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pTitle = new CTitle();
	VALIDATE(m_pTitle->Initialise(_iWidth, _iHeight));

	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	m_pGameover = new CGameover();
	VALIDATE(m_pGameover->Initialise(_iWidth, _iHeight));

	ShowCursor(false);

	return (true);
}

void
CGame::Draw()
{
	m_pBackBuffer->Clear();

	switch (m_eGameState)
	{
	case TITLE:
	{
		m_pTitle->Draw();
		break;
	}

	case INGAME:
	{
		m_pLevel->Draw();
		break;
	}
	
	case GAMEOVER:
	{
		m_pGameover->Draw();
		break;
	}

	default:break;
	}

	m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
	switch (m_eGameState)
	{
	case TITLE:
	{
		m_pTitle->Process(_fDeltaTick);
		break;
	}

	case INGAME:
	{
		m_pLevel->Process(_fDeltaTick);
		break;
	}

	case GAMEOVER:
	{
		m_pGameover->Process(_fDeltaTick);
		break;
	}

	default:break;
	}
}

void
CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();

	Process(fDT);
	Draw();

	m_pClock->Process();

	Sleep(1);
}

CGame&
CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}

	return (*s_pGame);
}

void
CGame::GameOverWon()
{
	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
CGame::GameOverLost()
{
	SetHighScores();
	SetGameState(GAMEOVER);
}

void CGame::GetHighScores()
{
	std::ifstream hFile("HighScores.txt");
	std::string line;

	while (std::getline(hFile, line))
	{
		m_vecHighScores.push_back(line);
	}

	hFile.close();
}

void CGame::SetHighScores()
{
	std::ofstream hFile("HighScores.txt");

	for (int i = 0; i < m_vecHighScores.size(); ++i)
	{
		hFile << m_vecHighScores[i];
		hFile << '\n';
	}

	hFile.close();
}

void CGame::SetGameState(EGameState _eGameState)
{
	m_eGameState = _eGameState;
}

void
CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

CBackBuffer*
CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

CLevel*
CGame::GetLevel()
{
	return (m_pLevel);
}

HINSTANCE
CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND
CGame::GetWindow()
{
	return (m_hMainWindow);
}