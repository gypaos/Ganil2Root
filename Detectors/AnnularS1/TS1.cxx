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
 *             format to a ROOT format for the S1 detector                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *   + WARNING: the label names are the one corresponding to MM5 (exp. e530) *
 *              This should be changed.                                      * 
 *                                                                           *
 *****************************************************************************/
#include "TS1.h"
#include "G2RDetectorManager.h"

#include <string>
#include <cstdlib>
using namespace std;


ClassImp(TS1)
////////////////////////////////////////////////////////////////////////////////
TS1::TS1(){
  // Default constructor
  fS1Data    = new TS1Data();
}


////////////////////////////////////////////////////////////////////////////////
TS1::~TS1(){
  delete fS1Data;
}


////////////////////////////////////////////////////////////////////////////////
bool TS1::Clear(){
  fS1Data->Clear();

  return true;
}


////////////////////////////////////////////////////////////////////////////////
bool TS1::Init(DataParameters *params){
  // internal mapping for S1
  ///////////
  // THETA //
  ///////////
  // we still want to record any data coming from unconnected mates
  for (int i = 0; i < 64; i++) {
    real_channelTh[i+1] = 64 + i+1;
  }

  // 1st quadrant theta
  real_channelTh[65] = 1;
  real_channelTh[66] = 2;
  real_channelTh[68] = 3;
  real_channelTh[67] = 4;
  real_channelTh[70] = 5;
  real_channelTh[69] = 6;
  real_channelTh[72] = 7;
  real_channelTh[71] = 8;
  real_channelTh[74] = 9;
  real_channelTh[73] = 10;
  real_channelTh[76] = 11;
  real_channelTh[75] = 12;
  real_channelTh[78] = 13;
  real_channelTh[77] = 14;
  real_channelTh[80] = 15;
  real_channelTh[79] = 16;

  // 2nd quadrant theta
  real_channelTh[82] = 17;
  real_channelTh[81] = 18;
  real_channelTh[84] = 19;
  real_channelTh[83] = 20;
  real_channelTh[86] = 21;
  real_channelTh[85] = 22;
  real_channelTh[88] = 23;
  real_channelTh[87] = 24;
  real_channelTh[90] = 25;
  real_channelTh[89] = 26;
  real_channelTh[92] = 27;
  real_channelTh[91] = 28;
  real_channelTh[94] = 29;
  real_channelTh[93] = 30;
  real_channelTh[95] = 31;
  real_channelTh[96] = 32;

  // 3rd quadrant theta
  real_channelTh[128] = 33;
  real_channelTh[127] = 34;
  real_channelTh[126] = 35;
  real_channelTh[125] = 36;
  real_channelTh[124] = 37;
  real_channelTh[123] = 38;
  real_channelTh[122] = 39;
  real_channelTh[121] = 40;
  real_channelTh[120] = 41;
  real_channelTh[119] = 42;
  real_channelTh[118] = 43;
  real_channelTh[117] = 44;
  real_channelTh[116] = 45;
  real_channelTh[115] = 46;
  real_channelTh[114] = 47;
  real_channelTh[113] = 48;

  // 4th quadrant theta
  real_channelTh[112] = 49;
  real_channelTh[111] = 50;
  real_channelTh[110] = 51;
  real_channelTh[109] = 52;
  real_channelTh[108] = 53;
  real_channelTh[107] = 54;
  real_channelTh[106] = 55;
  real_channelTh[105] = 56;
  real_channelTh[104] = 57;
  real_channelTh[103] = 58;
  real_channelTh[102] = 59;
  real_channelTh[101] = 60;
  real_channelTh[100] = 61;
  real_channelTh[99] = 62;
  real_channelTh[98] = 63;
  real_channelTh[97] = 64;

  /////////
  // PHI //
  /////////
  // we still want to record any data coming from unconnected mates
  /*
     for (int i = 0; i < 64; i++) {
     real_channelTh[i+1] = 64 + i+1;
     }
     */
  // 16 wedges phi
  real_channelPh[43] = 1;
  real_channelPh[41] = 2;
  real_channelPh[42] = 3;
  real_channelPh[44] = 4;
  real_channelPh[46] = 5;
  real_channelPh[48] = 6;
  real_channelPh[50] = 7;
  real_channelPh[52] = 8;
  real_channelPh[54] = 9;
  real_channelPh[56] = 10;
  real_channelPh[55] = 11;
  real_channelPh[53] = 12;
  real_channelPh[51] = 13;
  real_channelPh[49] = 14;
  real_channelPh[47] = 15;
  real_channelPh[45] = 16;

  bool status = false;

  vector<int> channum;
  int nbParams = params->GetNbParameters();
  int det;
  for (int index = 0; index < nbParams; index++) {
    int lbl    = params->GetLabel(index);
    string label = params->GetParNameFromIndex(index);
    //      cout << index << "  " << lbl << "  " << label << endl;

    if (label.compare(0,7,"MS1_STR") == 0 ) {  
      status = true;
      fLabelMap[lbl] = label;
      fDetectorManager->RegisterLabelToDetector(lbl,"AnnularS1")
      det = atoi(fLabelMap[lbl].substr(2,1).c_str());
      channum.push_back(det);
      if (label.compare(7,3,"X_E") == 0 ) {
        fTypeMap[lbl] = S1_ThE;
        channum.push_back(atoi(label.substr(10).c_str()));
        fParameterMap[lbl] = channum;                 //S1 STR signals 1-16 
        //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
      } 
      else if (label.compare(7,3,"X_T") == 0 ) {
        fTypeMap[lbl] = S1_ThT;
        channum.push_back(atoi(label.substr(10).c_str()));
        fParameterMap[lbl] = channum;                 //S1 STR signals 1-16
        //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
      } 
      else if (label.compare(7,3,"Y_E") == 0 ) {
        fTypeMap[lbl] = S1_PhE;
        channum.push_back(atoi(label.substr(10).c_str()));
        fParameterMap[lbl] = channum;                 //S1 STR signals 1-16 
        //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
      } 
      else if (label.compare(7,3,"Y_T") == 0 ) {
        fTypeMap[lbl] = S1_PhT;
        channum.push_back(atoi(label.substr(10).c_str()));
        fParameterMap[lbl] = channum;                 //S1 STR signals 1-16 
        //	    cout << fTypeMap[lbl] << "  " << fParameterMap[lbl] << endl;
      }
      else {
        cout << "TS1::Init() : problem reading S1's label -> "<< label << endl;
        status = false;
      }
    }
  }
  return status;
}


////////////////////////////////////////////////////////////////////////////////
bool TS1::Is(UShort_t lbl, Short_t val){
  bool status = false;
  switch (fTypeMap[lbl]) {

    case S1_ThE :{  
                   //cout<<  "- ---------< S1 Theta E >------------------!\n";
                   //cout<<lbl<<"S1 Theta E "<<val <<" | "<<fParameterMap[lbl]<<" "<<real_channelTh[fParameterMap[lbl]]<<endl;
                   fS1Data->SetS1ThetaEDetectorNbr(fParameterMap[lbl][0]);
                   fS1Data->SetS1ThetaEStripNbr(real_channelTh[fParameterMap[lbl][1]]);
                   fS1Data->SetS1ThetaEEnergy(val);
                   status = true;
                   break;
                 }

    case S1_ThT :{
                   //cout<<  " ----------< S1 Theta T >------------------!\n"; 
                   //cout<<lbl<<"S1 Theta T "<<val <<" | "<<fParameterMap[lbl]<<" "<<real_channelTh[fParameterMap[lbl]]<<endl;
                   fS1Data->SetS1ThetaTDetectorNbr(fParameterMap[lbl][0]);
                   fS1Data->SetS1ThetaTStripNbr(real_channelTh[fParameterMap[lbl][1]]);
                   fS1Data->SetS1ThetaTTime(val);
                   status = true;
                   break;
                 }

    case S1_PhE :{  
                   //cout<<  "- ---------< S1 Phi E >------------------!\n";
                   //cout<<lbl<<"S1 Phi E "<<val <<" | "<<fParameterMap[lbl]<<" "<<real_channelPh[fParameterMap[lbl]]<<endl;
                   fS1Data->SetS1PhiEDetectorNbr(fParameterMap[lbl][0]);
                   fS1Data->SetS1PhiEStripNbr(real_channelPh[fParameterMap[lbl][1]]);
                   fS1Data->SetS1PhiEEnergy(val);
                   status = true;
                   break;
                 }

    case S1_PhT :{
                   //cout<<  " ----------< S1 Phi T >------------------!\n"; 
                   //cout<<lbl<<"S1 Phi T "<<val <<" | "<<fParameterMap[lbl]<<" "<<real_channelPh[fParameterMap[lbl]]<<endl;
                   fS1Data->SetS1PhiTDetectorNbr(fParameterMap[lbl][0]);
                   fS1Data->SetS1PhiTStripNbr(real_channelPh[fParameterMap[lbl][1]]);
                   fS1Data->SetS1PhiTTime(val);
                   status = true;
                   break;
                 }

    default :{
               //cout<<"TS1::Is --> not a good label"<<endl;
               status = false;
             }
  } // end of switch

  return status;
}


////////////////////////////////////////////////////////////////////////////////
bool TS1::Treat(){
  return true;
}



void TS1::InitBranch(TTree *tree)
{
  tree->Branch("S1_ANNULAR", "TS1Data", &fS1Data);
}
