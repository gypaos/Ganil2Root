// 
// modified by Iulian 25/02/2011 finnished rdy for testing
// 
// 

#include <cstdlib>

#include "TLise.h"


ClassImp(TLise)

TLise::TLise()
{
   // Default constructor
   fLiseData    = new TLiseData();
}

TLise::~TLise()
{
   delete fLiseData;
}



bool TLise::Clear()
{
   fLiseData->Clear();

   return true;
}



bool TLise::Init(GDataParameters *params)
{
  bool status = false;

  Int_t nbParams = params->GetNbParameters();
  for (Int_t index = 0; index < nbParams; index++) {
      Int_t lbl    = params->GetLabel(index);
      string label = params->GetParName(index);
      //      cout << index << "  " << lbl << "  " << label << endl;
       
      if ((label.compare("E_D4"    ) == 0) || 
	  			(label.compare("TD4_HF"  ) == 0) ||
	  			(label.compare("GAL41_X" ) == 0) ||
	  			(label.compare("GAL41_Y" ) == 0) ||
	  			(label.compare("TGAL1_D4") == 0) ||
	  			(label.compare("GH_D4"   ) == 0) ||
	  			(label.compare("GB_D4"   ) == 0) ||
	  			(label.compare("DH_D4"   ) == 0) ||
	  			(label.compare("DB_D4"   ) == 0) ||
	  			(label.compare("E_D6"    ) == 0) ||
	  			(label.compare("TD6_HF"  ) == 0) ||
	  			(label.compare("GH_D6"   ) == 0) ||
	  			(label.compare("GB_D6"   ) == 0) ||
	  			(label.compare("DH_D6"   ) == 0) ||
	  			(label.compare("DB_D6"   ) == 0) ||
	  			(label.compare("E_GAMMA" ) == 0) ) {

	  fLabelMap[lbl] = label;
	  status = true;

	  if 			(label.compare("E_D4"    ) == 0 ) { fTypeMap[lbl] = E_D4    ; }
	  else if (label.compare("TD4_HF"  ) == 0 ) { fTypeMap[lbl] = TD4_HF  ; }
	  else if (label.compare("GAL41_X" ) == 0 ) { fTypeMap[lbl] = GAL41_X ; }
	  else if (label.compare("GAL41_Y" ) == 0 ) { fTypeMap[lbl] = GAL41_Y ; }
	  else if (label.compare("TGAL1_D4") == 0 ) { fTypeMap[lbl] = TGAL1_D4; }
	  else if (label.compare("GH_D4"   ) == 0 ) { fTypeMap[lbl] = GH_D4   ; }
	  else if (label.compare("GB_D4"   ) == 0 ) { fTypeMap[lbl] = GB_D4   ; }
	  else if (label.compare("DH_D4"   ) == 0 ) { fTypeMap[lbl] = DH_D4   ; }
	  else if (label.compare("DB_D4"   ) == 0 ) { fTypeMap[lbl] = DB_D4   ; }
	  else if (label.compare("E_D6"    ) == 0 ) { fTypeMap[lbl] = E_D6    ; }
	  else if (label.compare("TD6_HF"  ) == 0 ) { fTypeMap[lbl] = TD6_HF  ; }
	  else if (label.compare("GH_D6"   ) == 0 ) { fTypeMap[lbl] = GH_D6   ; }
	  else if (label.compare("GB_D6"   ) == 0 ) { fTypeMap[lbl] = GB_D6   ; }
 	  else if (label.compare("DH_D6"   ) == 0 ) { fTypeMap[lbl] = DH_D6   ; }
	  else if (label.compare("DB_D6"   ) == 0 ) { fTypeMap[lbl] = DB_D6   ; }
	  else if (label.compare("E_GAMMA" ) == 0 ) { fTypeMap[lbl] = E_GAMMA ; }
	  else 
	    {
	      cout << "TLise::Init() : problem reading LISE's label -> " << label << endl;
	      status = false;
	    }
	}
	}
      
      return status;
    }


bool TLise::Is(UShort_t lbl, Short_t val)
{
   bool status = false;

   switch (fTypeMap[lbl]) {

   case E_D4	  : {
     fLiseData->SetE_D4     (val);
     status = true;
     break;
   }
   case TD4_HF   : {
     fLiseData->SetTD4_HF  (val);
     status = true;
     break;
   }
   case GAL41_X   : {
     fLiseData->SetGAL41_X  (val);
     status = true;
     break;
   }
   case GAL41_Y   : {
     fLiseData->SetGAL41_Y  (val);
     status = true;
     break;
   }
   case TGAL1_D4  : {
     fLiseData->SetTGAL1_D4 (val);
     status = true;
     break;
   }
   case GH_D4 : {
     fLiseData->SetGH_D4(val);
     status = true;
     break;
   }
   case GB_D4 : {
     fLiseData->SetGB_D4(val);
     status = true;
     break;
   }
   case DH_D4 : {
     fLiseData->SetDH_D4(val);
     status = true;
     break;
   }
   case DB_D4 : {
     fLiseData->SetDB_D4(val);
     status = true;
     break;
   }
   case E_D6	  : {
     fLiseData->SetE_D6	    (val);
     status = true;
     break;
   }
   case TD6_HF   : {
     fLiseData->SetTD6_HF  (val);
     status = true;
     break;
   }
   case GH_D6 : {
     fLiseData->SetGH_D6(val);
     status = true;
     break;
   }
   case GB_D6 : {
     fLiseData->SetGB_D6(val);
     status = true;
     break;
   }
   case DH_D6 : {
     fLiseData->SetDH_D6(val);
     status = true;
     break;
   }
   case DB_D6 : {
     fLiseData->SetDB_D6(val);
     status = true;
     break;
   }
   case E_GAMMA   : {
     fLiseData->SetE_GAMMA  (val);
     status = true;
     break;
   }

   default:{
     //cout<< "TLise::Is --> not a good label"<<endl; 
     status = false;
     break;
   }
   } // end of switch

   return status;
}



bool TLise::Treat()
{
   return true;
}



void TLise::InitBranch(TTree *tree)
{
   tree->Branch("LISE", "TLiseData", &fLiseData);
}


