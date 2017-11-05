//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: gameover.h
// Description	: Gameover screen declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz
//

#pragma once

#if !defined(__GAMEOVER_H__)
#define __GAMEOVER_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CBackGround;

class CGameover
{
	// Member Functions
public:
	CGameover();
	virtual ~CGameover();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void DrawGameoverText();

protected:

private:
	CGameover(const CGameover& _kr);
	CGameover& operator= (const CGameover& _kr);

	// Member Variables
public:

protected:
	CBackGround* m_pBackground;

	int m_iWidth;
	int m_iHeight;
};

#endif    // __TITLE_H__