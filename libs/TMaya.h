/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: M. Vandebrouck   contact address: vandebro@ipno.in2p3.fr *
 *                  J. Gibelin                      gibelin@lpccaen.in2p3.fr *
 *                                                                           *
 * Creation Date  : November 2011                                            *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Maya detector                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#ifndef __MAYA__
#define __MAYA__

#include <string>
#include <vector>

#ifndef __DETECTOR__
#include "TDetector.h"
#endif

#ifndef __MAYADATA__
#include "TMayaData.h"
#endif

#include "GDataParameters.h"
#include "TTree.h"

#define	MAYA_QFIL_E	1
#define	MAYA_QFIL_T	2
#define	MAYA_PAD_E	3
#define	MAYA_PAD_E_CORR	4
#define	MAYA_SI_E	5
#define	MAYA_SI_T	6
#define	MAYA_CSI_E	7
#define	MAYA_CSI_T	8
#define	MAYA_FADC	9

#define	MAYA_TOF	10


class TMaya : public TDetector {
  public:
   TMaya();
   virtual ~TMaya();

   // virtual methods from TDetector
   virtual bool Init(GDataParameters*);
   virtual bool Clear();
   virtual bool Is(UShort_t, Short_t);
   virtual bool Treat();
   virtual void InitBranch(TTree*);
   virtual bool InitCalibrate(std::vector<string>&);
   virtual bool Calibrate();

   void Clear(const Option_t*) {};

   // getters and setters
   TMayaData*	GetMayaData() const {return fMayaData;}

  private:
   // Data class for Maya
   TMayaData  *fMayaData;

   ClassDef(TMaya,2)  // Ionisation Chamber with digitizer detector structure
};

#endif
