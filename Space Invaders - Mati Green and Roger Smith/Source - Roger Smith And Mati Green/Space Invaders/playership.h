//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: playership.h
// Description	: Player ship logic declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

#pragma once

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CPlayerShip : public CEntity
{
    // Member Functions
public:
    CPlayerShip();
    virtual ~CPlayerShip();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	bool IsHit() const;

protected:

private:
    CPlayerShip(const CPlayerShip& _kr);
    CPlayerShip& operator= (const CPlayerShip& _kr);

    // Member Variables
public:

protected:
	bool m_bHit;

private:

};

#endif    // __PADDLE_H__
