//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: title.h
// Description	: Title screen declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz
//

#pragma once

#if !defined(__TITLE_H__)
#define __TITLE_H__

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
class CBackGround;

class CTitle
{
	// Member Functions
public:
	CTitle();
	virtual ~CTitle();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:
	void DrawMenu();

private:
	CTitle(const CTitle& _kr);
	CTitle& operator= (const CTitle& _kr);

	// Member Variables
public:

protected:
	CBackGround* m_pBackground;

	int m_iWidth;
	int m_iHeight;
};

#endif    // __TITLE_H__