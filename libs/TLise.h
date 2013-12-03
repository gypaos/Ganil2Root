
				/*  */
/* Modified by Iulian 25/02/2011 Final version  rdy for testing*/
				/*  */

#ifndef __LISE__
#define __LISE__

#include <string>
#include <map>

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __LISE_ANDATA__
#include "TLiseData.h"
#endif


#include "TTree.h"

#define	E_D4       1
#define TD4_HF     2
#define GAL41_X    3
#define GAL41_Y    4
#define TGAL1_D4   5
#define GH_D4      6
#define GB_D4      7
#define	DH_D4      8
#define DB_D4      9
#define	E_D6       10
#define TD6_HF     11
#define GH_D6      12
#define GB_D6      13
#define	DH_D6      14
#define DB_D6      15
#define E_GAMMA    16



class TLise : public TDetector {
  public:
   TLise();
   virtual ~TLise();

   // virtual methods from TDetector
   virtual bool Init(GDataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);

   // getters and setters
   TLiseData*	GetLiseData() const {return fLiseData;}

  private:
   // Data class for Lise
   TLiseData  *fLiseData;

   ClassDef(TLise,1)  // Plastic detector structure
};

#endif
