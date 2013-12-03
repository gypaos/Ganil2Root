/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : March 2011                                               *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the SSSD detector (20 microns)    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TSSSD.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TSSSD)

TSSSD::TSSSD()
{
	// Default constructor
	fSSSDData    = new TSSSDData();
}

TSSSD::~TSSSD()
{
	delete fSSSDData;
}

bool TSSSD::Clear()
{
	fSSSDData->Clear();
	return true;
}

bool TSSSD::Init(GDataParameters *params)
{
	Int_t channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParName(index);

		if (label.compare(0,4,"SIMM") == 0 ) {
         status = true;
         fLabelMap[lbl]	= label;

         fTypeMap[lbl] = SSSD_E;
         channum = atoi(label.substr(6).c_str());
         fParameterMap[lbl] = channum;                 // SSSd E signals 1-16 
      } 
	} 
	
	return status;
}

bool TSSSD::Is(UShort_t lbl, Short_t val)
{
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
    
		case SSSD_E :
		{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(4,1).c_str());
			fSSSDData->SetEnergyDetectorNbr(det);
			fSSSDData->SetEnergyStripNbr(fParameterMap[lbl]);
			fSSSDData->SetEnergy(val);
			result = true;
			break;
		}
    
		default: 
		{
			result = false;
			break;
		}

	} // end switch
  
	return result;
}

bool TSSSD::Treat()
{
	return true;
}

void TSSSD::InitBranch(TTree *tree)
{
   tree->Branch("SSSD", "TSSSDData", &fSSSDData);
}

