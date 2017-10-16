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

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBrick::CBrick()
: m_bHit(false)
{

}

CBrick::~CBrick()
{

}

bool
CBrick::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

    return (true);
}

void
CBrick::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void
CBrick::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
        CEntity::Process(_fDeltaTick);
    }
}

void
CBrick::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
CBrick::IsHit() const
{
    return (m_bHit);
}

