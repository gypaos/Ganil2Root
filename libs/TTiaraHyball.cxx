/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : Nov 2013                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Tiara/Hyball detector         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TTiaraHyball.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TTiaraHyball)


TTiaraHyball::TTiaraHyball()
{
	// Default constructor
	fTiaraHyballData    = new TTiaraHyballData();
}



TTiaraHyball::~TTiaraHyball()
{
	delete fTiaraHyballData;
}



bool TTiaraHyball::Clear()
{
	fTiaraHyballData->Clear();
	return true;
}



bool TTiaraHyball::Init(GDataParameters *params)
{
	Int_t wedge, channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParName(index);

		if (label.compare(0,7,"TIA_HYB") == 0 ) 
		{
			status = true;
			fLabelMap[lbl]	 = label;
	     
			if (label.compare(10,1,"R") == 0 ) 
			{
				fTypeMap[lbl] = HYB_RING_E;
            // wedge number
				wedge = atoi(label.substr(9,1).c_str());        // wedge number 0 - 7
            // ring number
				channum = atoi(label.substr(11).c_str());       // ring number 0 - 15
				fParameterMap[lbl] = (wedge-1)*16 + channum-1;
			} 
			else if (label.compare(10,1,"S") == 0 ) 
			{
				fTypeMap[lbl] = HYB_SECT_E;
            // wedge number
				wedge = atoi(label.substr(9,1).c_str());        // wedge number 0 - 7
            // sector number
				channum = atoi(label.substr(11).c_str());       // sector number 0 - 7
				fParameterMap[lbl] = (wedge-1)*8 + channum-1;
			}
			else 
			{
				cout << "TTiaraHyball::Init() : problem reading Tiara/Hyball label -> " << label << endl;
				status = false;
			}
		}
	} 
	
	return status;
}

bool TTiaraHyball::Is(UShort_t lbl, Short_t val)
{
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
    
		case HYB_RING_E :
		{  
			//cout<<  "- ---------< HYB RING E >------------------!\n";
			fTiaraHyballData->SetRingEDetectorNbr(fParameterMap[lbl] / 16+1);
			fTiaraHyballData->SetRingEStripNbr(fParameterMap[lbl] % 16+1);
			fTiaraHyballData->SetRingEEnergy(val);
			fTiaraHyballData->SetRingTDetectorNbr(fParameterMap[lbl] / 16+1);
			fTiaraHyballData->SetRingTStripNbr(fParameterMap[lbl] % 16+1);
			fTiaraHyballData->SetRingTTime(0);
			result = true;
			break;
		}
    
		case HYB_SECT_E :
		{  
			//cout<<  "- ---------< HYB SECT E >------------------!\n";
			fTiaraHyballData->SetSectorEDetectorNbr(fParameterMap[lbl] / 8+1);
			fTiaraHyballData->SetSectorEStripNbr(fParameterMap[lbl] % 8+1);
			fTiaraHyballData->SetSectorEEnergy(val);
			fTiaraHyballData->SetSectorTDetectorNbr(fParameterMap[lbl] / 8+1);
			fTiaraHyballData->SetSectorTStripNbr(fParameterMap[lbl] % 8+1);
			fTiaraHyballData->SetSectorTTime(0);
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

bool TTiaraHyball::Treat()
{
	return true;
}

void TTiaraHyball::InitBranch(TTree *tree)
{
   tree->Branch("TiaraHyball", "TTiaraHyballData", &fTiaraHyballData);
}

