/*****************************************************************************
 * Copyright (C) 2008-2017   this file is part of the Ganil2Root Project     *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                  J. Burgunder                    burgunder@ganil.in2p3.fr *
 *  Update        : M. Moukaddam                                             *
 *  Update        : V. Alcindor                                              *
 *                                                                           *
 * Creation Date  : May 2009                                                 *
 * Last update    : June 2017                                                *
 * Last update    : May 2018                                                 *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Exl detector                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + june 2017: Add support for G2R::ExlPhysics from NPTool               *
 *                                                                           *
 *****************************************************************************/
#include "G2RExl.h"
#include "G2RDetectorFactory.h"
#include <string>
#include <cstdlib>
using namespace std;


ClassImp(G2R::Exl)
////////////////////////////////////////////////////////////////////////////////
G2R::Exl::Exl(){
	// Default constructor
	fExlData    = new TExlData();
  // Initialise the generic pointer from base class
  m_Data = fExlData;
}
////////////////////////////////////////////////////////////////////////////////
G2R::Exl::~Exl(){
	delete fExlData;
}

////////////////////////////////////////////////////////////////////////////////

bool G2R::Exl::Clear()
{
	fExlData->Clear();
	return true;
}
////////////////////////////////////////////////////////////////////////////////

bool G2R::Exl::Init(DataParameters *params){ 
	Int_t channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) {
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParNameFromIndex(index);

		if(label.compare(0,3,"EXL") == 0 ){
			status = true;
			fLabelMap[lbl] = label;

			if(label.compare(0,5,"EXL_E") == 0 ){
				fTypeMap[lbl] = EXL_E;
				channum = atoi(label.substr(5).c_str());
				//fParameterMap[lbl] = channum;                 // EXL E signals 1-18 
				// cout << "Label: "<< label <<  " Energy chan number: "  << channum << endl;
			}
			else if(label.compare(0,5,"EXL_T") == 0 ){
				fTypeMap[lbl] = EXL_T;
				channum = atoi(label.substr(5).c_str());
				//fParameterMap[lbl] = channum;                 // EXL T signals 1-18 
        }
			/* else if(label.compare(0,6,"EXL_HF") == 0 ) */
			/* { */
			/* 	fTypeMap[lbl] = EXL_HF; */
			/* 	channum = atoi(label.substr(5).c_str()); */
			/* 	fParameterMap[lbl] = channum;                 //EXL signals 1-18 */ 
			/* 	//cout << "Label: "<< label <<  " Energy chan number: "  << channum << endl; */
			/* } */
			else{
				cout << "G2R::Exl::Init() : problem reading EXL label -> " << label << endl;
				status = false;
			}
		}
	} 
	
	return status;
}
////////////////////////////////////////////////////////////////////////////////

bool G2R::Exl::Is(UShort_t lbl, Short_t val){
	Int_t det;
	Int_t cry;
	bool result = false;

	switch (fTypeMap[lbl]){ 

		case EXL_E :{  
			//cout<<  "- ---------< EXL E >------------------!\n";
      //cout << " Label in Map " <<  fLabelMap[lbl] << " cry " << cry << "    val " << val << endl;
			cry = atoi(fLabelMap[lbl].substr(fLabelMap[lbl].find("_E")+2).c_str());
      // cout << "fLabelMap[lbl].substr(fLabelMap[lbl].find(_E)+2).c_str() : "
      // << fLabelMap[lbl].substr(fLabelMap[lbl].find("_E")+2).c_str() 
      // << " lbl : " << lbl 
      // << " cry : " << cry << endl;
			fExlData->SetEnergy(1, cry, val);
			result = true;
			break;
		}

		case EXL_T :{  
			//cout<<  "- ---------< EXL T >------------------!\n";
      //cout << " Label in Map " <<  fLabelMap[lbl] << " cry " << cry << "    val " << val << endl;
			cry = atoi(fLabelMap[lbl].substr( fLabelMap[lbl].find("_T")+2 ).c_str());
			fExlData->SetTime(1, cry, val);
			result = true;
			break;
		}
    
		// case EXL_HF :{
		// 	//cout<<  " ----------< EXL T >------------------!\n"; 
		// 	cry = atoi(fLabelMap[lbl].substr(2,1).c_str());
		// 	//fExlData->SetTime(det,fParameterMap[lbl],val);
		// 	result = true;
		// 	break;
		// }

		default: {
			result = false;
			break;
		}

	} // end switch
  
	return result;
}

////////////////////////////////////////////////////////////////////////////////
bool G2R::Exl::Treat(){
	return true;
}

////////////////////////////////////////////////////////////////////////////////
void G2R::Exl::InitBranch(TTree *tree){
   tree->Branch("EXL", "TExlData", &fExlData);
}

////////////////////////////////////////////////////////////////////////////////
//            Construct Method to be pass to the DetectorFactory              //
////////////////////////////////////////////////////////////////////////////////
G2R::VDetector* G2R::Exl::Construct(){
  return (G2R::VDetector*) new G2R::Exl();
}

////////////////////////////////////////////////////////////////////////////////
//            Registering the construct method to the factory                 //
////////////////////////////////////////////////////////////////////////////////
extern "C"{
class proxy_g2r_exl{
  public:
    proxy_g2r_exl(){
      G2R::DetectorFactory::getInstance()->AddToken("EXL","EXL");
      G2R::DetectorFactory::getInstance()->AddDetector("EXL",G2R::Exl::Construct);
    }
};

proxy_g2r_exl p_g2r_exl;
}


