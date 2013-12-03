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
 *             format to a ROOT format for the Tiara/Barrel detector         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TTiaraBarrel.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TTiaraBarrel)

TTiaraBarrel::TTiaraBarrel()
{
	// Default constructor
	fTiaraBarrelData    = new TTiaraBarrelData();
}



TTiaraBarrel::~TTiaraBarrel()
{
	delete fTiaraBarrelData;
}



bool TTiaraBarrel::Clear()
{
	fTiaraBarrelData->Clear();
	return true;
}



bool TTiaraBarrel::Init(GDataParameters *params)
{
	Int_t barrel, channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParName(index);

		if (label.compare(0,3,"TIA") == 0  &&  label.compare(5,3,"BAR") == 0) 
		{
			status = true;
			fLabelMap[lbl]	 = label;
	     
			if (label.compare(4,1,"I") == 0) {             // inner barrel
            if (label.compare(13,1,"U") == 0) {
               fTypeMap[lbl] = IBAR_UP_STRIP_E;
               // barrel number
               barrel = atoi(label.substr(10,1).c_str());      // barrel number 0 - 7
               // strip number
               channum = atoi(label.substr(12,1).c_str());     // strip number 0 - 3
               fParameterMap[lbl] = barrel*4 + channum; 
            } 
            else if (label.compare(13,1,"D") == 0) {
               fTypeMap[lbl] = IBAR_DO_STRIP_E;
               // barrel number
               barrel = atoi(label.substr(10,1).c_str());      // barrel number 0 - 7
               // strip number
               channum = atoi(label.substr(12,1).c_str());     // strip number 0 - 3
               fParameterMap[lbl] = barrel*4 + channum; 
            }
            else if (label.compare(11,3,"BCK") == 0) {
               fTypeMap[lbl] = IBAR_BACK_E;
               channum = atoi(label.substr(10,1).c_str());     // barrel number 0 - 7
               fParameterMap[lbl] = channum; 
            }
         }
         else if (label.compare(4,1,"O") == 0) {
            fTypeMap[lbl] = OBAR_E;
            // barrel number
            barrel = atoi(label.substr(10,1).c_str());      // barrel number 0 - 7
            // strip number
            channum = atoi(label.substr(12,1).c_str());     // strip number 0 - 3
            fParameterMap[lbl] = barrel*4 + channum; 
         }
         else 
         {
            cout << "TTiaraBarrel::Init() : problem reading Tiara/Barrel label -> " << label << endl;
            status = false;
         }
      }
   }

   return status;
}



bool TTiaraBarrel::Is(UShort_t lbl, Short_t val)
{
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
		case IBAR_UP_STRIP_E :
		{  
			//cout<<  "- --------- IBAR UP E  >------------------!\n";
			fTiaraBarrelData->Set_FrontUpstreamE_DetectorNbr(fParameterMap[lbl] / 4);
			fTiaraBarrelData->Set_FrontUpstreamE_StripNbr(fParameterMap[lbl] % 4);
			fTiaraBarrelData->Set_FrontUpstreamE_Energy(val);
			fTiaraBarrelData->Set_FrontUpstreamT_DetectorNbr(fParameterMap[lbl] / 4);
			fTiaraBarrelData->Set_FrontUpstreamT_StripNbr(fParameterMap[lbl] % 4);
			fTiaraBarrelData->Set_FrontUpstreamT_Time(0);
			result = true;
			break;
		}
    
		case IBAR_DO_STRIP_E :
		{  
			//cout<<  "- --------- IBAR DOWN E  >------------------!\n";
			fTiaraBarrelData->Set_FrontDownstreamE_DetectorNbr(fParameterMap[lbl] / 4);
			fTiaraBarrelData->Set_FrontDownstreamE_StripNbr(fParameterMap[lbl] % 4);
			fTiaraBarrelData->Set_FrontDownstreamE_Energy(val);
			fTiaraBarrelData->Set_FrontDownstreamT_DetectorNbr(fParameterMap[lbl] / 4);
			fTiaraBarrelData->Set_FrontDownstreamT_StripNbr(fParameterMap[lbl] % 4);
			fTiaraBarrelData->Set_FrontDownstreamT_Time(0);
			result = true;
			break;
		}
    
		case IBAR_BACK_E :
		{  
			//cout<<  "- --------- IBAR BACK E  >------------------!\n";
			fTiaraBarrelData->Set_BackE_DetectorNbr(fParameterMap[lbl]);
			fTiaraBarrelData->Set_BackE_Energy(val);
			fTiaraBarrelData->Set_BackT_DetectorNbr(fParameterMap[lbl]);
			fTiaraBarrelData->Set_BackT_Time(0);
			result = true;
			break;
		}
    
		case OBAR_E :
		{  
			//cout<<  "- --------- OBAR E  >------------------!\n";
			fTiaraBarrelData->Set_OuterE_DetectorNbr(fParameterMap[lbl] / 4);
			fTiaraBarrelData->Set_OuterE_StripNbr(fParameterMap[lbl] % 4);
			fTiaraBarrelData->Set_OuterE_Energy(val);
			fTiaraBarrelData->Set_OuterT_DetectorNbr(fParameterMap[lbl] / 4);
			fTiaraBarrelData->Set_OuterT_StripNbr(fParameterMap[lbl] % 4);
			fTiaraBarrelData->Set_OuterT_Time(0);
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



bool TTiaraBarrel::Treat()
{
	return true;
}



void TTiaraBarrel::InitBranch(TTree *tree)
{
   tree->Branch("TiaraBarrel", "TTiaraBarrelData", &fTiaraBarrelData);
}

