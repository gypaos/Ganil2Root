#ifndef __ChateauCristal__
#define __ChateauCristal__

#include <string>
#include <map>

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __ChateauCristalDATA__
#include "TChateauCristalData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define ChateauCristalE  1
#define ChateauCristalT  2

class TChateauCristal : public TDetector 
{
 
 public:
	TChateauCristal();
	virtual ~TChateauCristal();

	// virtual methods from TDetector
	virtual bool Init(GDataParameters*);
	virtual bool Clear();
	virtual bool Is(UShort_t, Short_t);
	virtual bool Treat();
	virtual void InitBranch(TTree*);

	TChateauCristalData*	GetChateauCristalData()       const {return fChateauCristalData;}

 private:
	TChateauCristalData  *fChateauCristalData;

	ClassDef(TChateauCristal,2)  // ChateauCristal detector structure
};

#endif
