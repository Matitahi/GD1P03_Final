//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: mysteryship.h
// Description	: Mystery ship logic declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

#if !defined(__MYSTERYSHIP_H__)
#define __MYSTERYSHIP_H__

// Local Includes
#include "entity.h"

class CMysteryShip : public CEntity
{
	// Member Functions
public:
	CMysteryShip();

	virtual ~CMysteryShip();

	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX);

	virtual void Draw();

	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);

	void SetVelocityX(float _fX);

	bool IsHit() const;

private:
	CMysteryShip(const CMysteryShip& _kr);
	CMysteryShip& operator= (const CMysteryShip& _kr);

protected:
	// Member Variables
	float m_fVelocityX;
	bool m_bHit;
};

#endif    // __MYSTERYSHIP_H__
