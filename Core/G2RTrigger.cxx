/*****************************************************************************
 * Copyright (C) 2008   this file is part of the Ganil2Root Project          *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                  J. Burgunder                    burgunder@ganil.in2p3.fr *
 *                                                                           *
 * Creation Date  : May 2009                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the GMT module                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "G2RTrigger.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(G2R::Trigger)
////////////////////////////////////////////////////////////////////////////////
G2R::Trigger::Trigger(){
	// Default constructor
	fTriggerData    = new TTriggerData();
}

G2R::Trigger::~Trigger(){
	delete fTriggerData;
}
////////////////////////////////////////////////////////////////////////////////
bool G2R::Trigger::Clear(){
	fTriggerData->Clear();
	return true;
}
////////////////////////////////////////////////////////////////////////////////
bool G2R::Trigger::Init(DataParameters *params){
	bool status = false;

	Int_t nbParams = params->GetNbParameters();
	for (Int_t index = 0; index < nbParams; index++) {
		Int_t lbl    = params->GetLabel(index);
		string label = params->GetParNameFromIndex(index);
		//cout << index << "  " << lbl << "  " << label <<  endl;
       
		if (label.compare(0,7,"GATCONF") == 0) {  
			fLabelMap[lbl] = label;
			fTypeMap[lbl] = TRIG_1;
			status = true;
			//cout << fTypeMap[lbl] << endl;
		} 
		else if (label.compare(0,6,"INCONF") == 0) {
			fLabelMap[lbl] = label;
			fTypeMap[lbl] = TRIG_2;
			status = true;
			//cout << fTypeMap[lbl] << endl;
		} 
		else 
		{
			//cout << "G2R::Trigger::Init() : problem reading Trigger's label" << endl;
			status = false;
		}
	}
   
	return status;
}
////////////////////////////////////////////////////////////////////////////////
bool G2R::Trigger::Is(UShort_t lbl, Short_t val){
	bool status = false;

	switch (fTypeMap[lbl]) {
		case TRIG_1 :{  
			//cout<<  "- ---------< Trigger 1 >------------------!\n";
			fTriggerData->SetTRIG1(val);
			status = true;
			break;
		}
  
		case TRIG_2 :{  
			//cout<<  "- ---------< Trigger 2 >------------------!\n";
			fTriggerData->SetTRIG2(val);
			status = true;
			break;
		}

		case TRIG_3 :{  
			//cout<<  "- ---------< Trigger 3 >------------------!\n";
			fTriggerData->SetTRIG3(val);
			status = true;
			break;
		}
  
		case TRIG_4 :{  
			//cout<<  "- ---------< Trigger 4 >------------------!\n";
			fTriggerData->SetTRIG4(val);
			status = true;
			break;
		}
  
		case TRIG_5 :{  
			//cout<<  "- ---------< Trigger 5 >------------------!\n";
			fTriggerData->SetTRIG5(val);
			status = true;
			break;
		}
    
		default:{
			//cout<<"G2R::Trigger::Is --> not a good label"<<endl;
			status = false;
		}
	}
  
   return status;
}
////////////////////////////////////////////////////////////////////////////////
bool G2R::Trigger::Treat(){
	return true;
}
////////////////////////////////////////////////////////////////////////////////
void G2R::Trigger::InitBranch(TTree *tree){
	tree->Branch("TRIG", "TTriggerData", &fTriggerData);
}

