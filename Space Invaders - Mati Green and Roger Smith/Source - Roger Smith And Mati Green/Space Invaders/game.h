//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: game.h
// Description	: Game logic declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <vector>

// Local Includes
#include "clock.h"
#include "title.h"
#include "gameover.h"

// Types
enum EGameState
{
	DEFAULT = 0,
	TITLE = 1,
	INGAME = 2,
	GAMEOVER = 3,
};

// Constants

// Prototypes
class CLevel;
class CBackBuffer;

class CGame
{
	// Member Functions
public:
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void ExecuteOneFrame();

	CBackBuffer* GetBackBuffer();
	CLevel* GetLevel();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	void GameOverWon();
	void GameOverLost();

	void GetHighScores();
	void SetHighScores();

	void SetGameState(EGameState _eGameState);

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

protected:

private:
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

	// Member Variables
public:

protected:
	CClock* m_pClock;
	CTitle* m_pTitle;
	CLevel* m_pLevel;
	CGameover* m_pGameover;

	CBackBuffer* m_pBackBuffer;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static CGame* s_pGame;

	std::vector<std::string> m_vecHighScores;

	EGameState m_eGameState;

private:

};

#endif    // __GAME_H__

