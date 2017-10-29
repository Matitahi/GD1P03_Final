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
	CEnemy(int _iType);

	CEnemy();

	virtual ~CEnemy();

	virtual bool Initialise();

	virtual void Draw();

	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);

	int GetType();

	bool IsHit() const;

private:
	CEnemy(const CEnemy& _kr);
	CEnemy& operator= (const CEnemy& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;
	int m_iType;
};


#endif    // __ENEMY_H__