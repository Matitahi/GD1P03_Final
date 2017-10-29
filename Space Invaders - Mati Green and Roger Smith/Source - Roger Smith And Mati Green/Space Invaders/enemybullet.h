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

private:
	CEnemyBullet(const CEnemyBullet& _kr);
	CEnemyBullet& operator= (const CEnemyBullet& _kr);

protected:
	float m_fVelocityY;


};


#endif    // __ENEMYBULLET_H__

