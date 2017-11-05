//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: enemy.h
// Description	: Enemy logic implementation file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz
//

#if !defined(__ENEMY_H__)
#define __ENEMY_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CEnemy : public CEntity
{
	// Member Functions
public:
	CEnemy(int _iType, float _fSpeed);

	CEnemy();

	virtual ~CEnemy();

	virtual bool Initialise();

	virtual void Draw();

	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);

	int GetType();

	bool IsHit() const;

	void ChangeDirection();

	bool MovingRight() const;

	void CanMove(bool _bMovement);

private:
	CEnemy(const CEnemy& _kr);
	CEnemy& operator= (const CEnemy& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;
	int m_iType;
	bool m_bMoveRight;
	bool m_bCanMove;
	int m_iStepTick;
	int m_iStepFreq;
	float m_fSpeed;
};


#endif    // __ENEMY_H__