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


protected:

private:
    CPlayerShip(const CPlayerShip& _kr);
    CPlayerShip& operator= (const CPlayerShip& _kr);

    // Member Variables
public:

protected:

private:

};

#endif    // __PADDLE_H__
