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

#if !defined(__BARRIER_H__)
#define __BARRIER_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CBarrier : public CEntity
{
	// Member Functions
public:
	CBarrier();

	virtual ~CBarrier();

	virtual bool Initialise();

	virtual void Draw();

	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);

	bool IsHit() const;

	void ReduceHp();

private:
	CBarrier(const CBarrier& _kr);
	CBarrier& operator= (const CBarrier& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;
	int m_iHp;
};


#endif    // __BARRIER_H__
