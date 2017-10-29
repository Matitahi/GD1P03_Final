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

#if !defined(__BALL_H__)
#define __BALL_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h" // for GetAsyncKeyState

// Types

// Constants

// Prototypes
class CSprite;

class CPlayerBullet : public CEntity
{
    // Member Functions
public:
    CPlayerBullet();
    virtual ~CPlayerBullet();

    virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);
    void SetVelocityY(float _fY);
	void SetHit(bool _b);
	bool IsHit() const;
    float GetRadius() const;

protected:

private:
    CPlayerBullet(const CPlayerBullet& _kr);
    CPlayerBullet& operator= (const CPlayerBullet& _kr);

    // Member Variables
public:

protected:
    float m_fVelocityX;
    float m_fVelocityY;
	bool m_bHit;

private:

};


#endif    // __BALL_H__
