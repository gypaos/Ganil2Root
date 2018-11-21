/*****************************************************************************
 * Copyright (C) 2008-2017   this file is part of the Ganil2Root Project     *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                  J. Burgunder                    burgunder@ganil.in2p3.fr *
 *                                                                           *
 * Creation Date  : May 2009                                                 *
 * Last update    : March 2011                                               *
 *---------------------------------------------------------------------------*
 * Decription: This class is in charged of converting raw data from GANIL    *
 *             format to a ROOT format for the Must2 detector                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *    + march 2011: Add support for G2R::Must2Physics from NPTool            *
 *                                                                           *
 *****************************************************************************/
#include "G2RMust2.h"
#include "G2RDetectorFactory.h"
#include "G2RDetectorManager.h"
#include <string>
#include <cstdlib>
using namespace std;


ClassImp(G2R::Must2)
////////////////////////////////////////////////////////////////////////////////
G2R::Must2::Must2(){
	// Default constructor
	fMust2Data    = new TMust2Data();
  // Initialise the generic pointer from base class
  m_Data = fMust2Data;
}
////////////////////////////////////////////////////////////////////////////////
G2R::Must2::~Must2(){
	delete fMust2Data;
}

////////////////////////////////////////////////////////////////////////////////

bool G2R::Must2::Clear()
{
	fMust2Data->Clear();
	return true;
}
////////////////////////////////////////////////////////////////////////////////

bool G2R::Must2::Init(DataParameters *params){ 
	vector<int> channum;
	int nbParams = params->GetNbParameters();
	bool status = false;
  int det=-1;
	for (Int_t index = 0; index < nbParams; index++) {
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParNameFromIndex(index);

		if (label.compare(0,2,"MM") == 0 ) {
			status = true;
			fLabelMap[lbl]	 = label;
	    fDetectorManager->RegisterLabelToDetector(lbl,"MUST2"); 
			det = atoi(fLabelMap[lbl].substr(2,1).c_str());
		  channum.clear();
      channum.push_back(det);

      if (label.compare(4,6,"STRX_E") == 0 ) {
				fTypeMap[lbl] = MUST2STR_XE;
				channum.push_back(atoi(label.substr(10).c_str()));
				fParameterMap[lbl] = channum;                 //MM STR X-E signals 1-128 
			} 

			else if (label.compare(4,6,"STRX_T") == 0 ) {
				fTypeMap[lbl] = MUST2STR_XT;
				channum.push_back(atoi(label.substr(10).c_str()));
				fParameterMap[lbl] = channum;                 //MM STR X-T signals 1-128
			}

			else if (label.compare(4,6,"STRY_E") == 0 ) {
				fTypeMap[lbl] = MUST2STR_YE;
				channum.push_back(atoi(label.substr(10).c_str()));
				fParameterMap[lbl] = channum;                 //MM STR Y-E signals 1-128 
			} 

			else if (label.compare(4,6,"STRY_T") == 0 ) {
				fTypeMap[lbl] = MUST2STR_YT;
				channum.push_back(atoi(label.substr(10).c_str()));
				fParameterMap[lbl] = channum;                 //MM STR Y-T signals 1-128 
			}
			
      else if (label.compare(4,6,"SILI_E") == 0 ) {
				fTypeMap[lbl] = MUST2SILI_E;
				channum.push_back(atoi(label.substr(10).c_str()));
				fParameterMap[lbl] = channum;                 //MM SILI E signals 1-16
			} 

			else if (label.compare(4,6,"SILI_T") == 0 ) {
				fTypeMap[lbl] = MUST2SILI_T;
				channum.push_back(atoi(label.substr(10).c_str()));
				fParameterMap[lbl] = channum;                 //MM SILI T signals 1-16
			}
			
      else if (label.compare(4,5,"CSI_E") == 0 ) {
				fTypeMap[lbl] = MUST2CSI_E;
				channum.push_back(atoi(label.substr(9).c_str()));
				fParameterMap[lbl] = channum;                 //MM CsI E signals 1-16
			} 

			else if (label.compare(4,5,"CSI_T") == 0 ) {
				fTypeMap[lbl] = MUST2CSI_T;
				channum.push_back(atoi(label.substr(9).c_str()));
				fParameterMap[lbl] = channum;                 //MM CsI T signals 1-16 
			} 

			else{
				cout << "G2R::Must2::Init() : problem reading MUST2 label -> " << label << endl;
				status = false;
			}
		}
	} 
	
	return status;
}
////////////////////////////////////////////////////////////////////////////////

bool G2R::Must2::Is(UShort_t lbl, Short_t val){
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]){
    
		case MUST2STR_XE :{  
			//cout<<  "- ---------< STR X E >------------------!\n";
			fMust2Data->SetStripXE(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}
    
		case MUST2STR_XT :{
			//cout<<  " ----------< STR X T >------------------!\n"; 
			fMust2Data->SetStripXT(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}

		case MUST2STR_YE :{  
			//cout<<  "- ---------< STR Y E >------------------!\n";
			fMust2Data->SetStripYE(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}
    
		case MUST2STR_YT :{
			//cout<<  " ----------< STR Y T >------------------!\n"; 
			fMust2Data->SetStripYT(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}

		case MUST2SILI_E :{  
			//cout<<  "- ---------<  SILI E >------------------!\n";
			fMust2Data->SetSiLiE(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}
    
		case MUST2SILI_T :{
			//cout<<  " ----------<  SILI T >------------------!\n"; 
			fMust2Data->SetSiLiT(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}

		case MUST2CSI_E :{  
			//cout<<  "- ---------<  CSI E  >------------------!\n";
			fMust2Data->SetCsIE(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}
    
		case MUST2CSI_T :{
			//cout<<  " ----------<  CSI T  >------------------!\n"; 
			fMust2Data->SetCsIT(fParameterMap[lbl][0],fParameterMap[lbl][1],val);
			result = true;
			break;
		}

		default: {
			result = false;
			break;
		}

	} // end switch
  
	return result;
}

////////////////////////////////////////////////////////////////////////////////
bool G2R::Must2::Treat(){
	return true;
}

////////////////////////////////////////////////////////////////////////////////
void G2R::Must2::InitBranch(TTree *tree){
   tree->Branch("MUST2", "TMust2Data", &fMust2Data);
}

////////////////////////////////////////////////////////////////////////////////
//            Construct Method to be pass to the DetectorFactory              //
////////////////////////////////////////////////////////////////////////////////
G2R::VDetector* G2R::Must2::Construct(){
  return (G2R::VDetector*) new G2R::Must2();
}

////////////////////////////////////////////////////////////////////////////////
//            Registering the construct method to the factory                 //
////////////////////////////////////////////////////////////////////////////////
extern "C"{
class proxy_g2r_must2{
  public:
    proxy_g2r_must2(){
      G2R::DetectorFactory::getInstance()->AddToken("M2Telescope","MUST2");
      G2R::DetectorFactory::getInstance()->AddDetector("M2Telescope",G2R::Must2::Construct);
    }
};

proxy_g2r_must2 p_g2r_must2;
}

