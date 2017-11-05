//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: barrier.h
// Description	: Barrier logic declaration file
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

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
	void SetHp(int _iHp);

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
