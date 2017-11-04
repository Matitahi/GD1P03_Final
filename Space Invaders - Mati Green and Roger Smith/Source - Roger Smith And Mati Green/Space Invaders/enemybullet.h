//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: enemybullet.h
// Description	: Enemy bullet logic declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

#if !defined(__ENEMYBULLET_H__)
#define __ENEMYBULLET_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CEnemyBullet : public CEntity
{
	// Member Functions
public:
	CEnemyBullet();

	virtual ~CEnemyBullet();

	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY);

	virtual void Draw();

	virtual void Process(float _fDeltaTick);

	float GetVelocityY() const;

	void SetVelocityY(float _fY);

	float GetRadius() const;

	void SetHit(bool _bHit);
	bool IsHit() const;

private:
	CEnemyBullet(const CEnemyBullet& _kr);
	CEnemyBullet& operator= (const CEnemyBullet& _kr);

protected:
	float m_fVelocityY;
	bool m_bHit;
};


#endif    // __ENEMYBULLET_H__

