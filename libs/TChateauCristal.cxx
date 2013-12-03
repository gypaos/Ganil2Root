#include <cstdlib>

#include "TChateauCristal.h"

ClassImp(TChateauCristal)

TChateauCristal::TChateauCristal()
{
	fChateauCristalData    = new TChateauCristalData();
}

TChateauCristal::~TChateauCristal()
{
	delete fChateauCristalData;
}

bool TChateauCristal::Clear()
{
	fChateauCristalData->Clear();
	return true;
}

bool TChateauCristal::Init(GDataParameters *params)
{
	Int_t channum;
	Int_t nbParams = params->GetNbParameters();
	bool status = false;

	for (Int_t index = 0; index < nbParams; index++) 
	{
		Int_t lbl      = params->GetLabel(index);
		string label   = params->GetParName(index);

		if (label.compare(1,3,"BaF") == 0 ) 
		{
			status = true;
			fLabelMap[lbl]	 = label;
	     
			if (label.compare(0,1,"E") == 0 ) 
			{
				fTypeMap[lbl] = ChateauCristalE;
				channum = atoi(label.substr(5).c_str());
				//cout << label << "    " << channum << endl;
				fParameterMap[lbl] = channum;                 //ChateauCristal Energy 
			} 
			else if (label.compare(0,1,"T") == 0 ) 
			{
				fTypeMap[lbl] = ChateauCristalT;
				channum = atoi(label.substr(5).c_str());
				//cout << label << "    " << channum << endl;
				fParameterMap[lbl] = channum;                 //ChateauCristal Time 
			} 
			else 
			{
				cout << "TChateauCristal::Init() : problem reading ChateauCristal label -> " << label << endl;
				status = false;
			}
		}
	} 
	
	return status;
}

bool TChateauCristal::Is(UShort_t lbl, Short_t val)
{
	Int_t det;
	bool result = false;

	switch (fTypeMap[lbl]) 
	{
    
		case ChateauCristalE :
		{  
			//cout<<  "- ---------< ChateauCristal E >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(5,2).c_str());
			fChateauCristalData->SetChateauCristalEDetectorNbr(det);
			//cout << det << endl;
			fChateauCristalData->SetChateauCristalEnergy(val);
			result = true;
			break;
		}
    
		case ChateauCristalT :
		{  
			//cout<<  "- ---------< ChateauCristal T >------------------!\n";
			det = atoi(fLabelMap[lbl].substr(5,2).c_str());
			fChateauCristalData->SetChateauCristalTDetectorNbr(det);
			//cout << det << endl;
			fChateauCristalData->SetChateauCristalTime(val);
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

bool TChateauCristal::Treat()
{
	return true;
}

void TChateauCristal::InitBranch(TTree *tree)
{
   tree->Branch("ChateauCristal", "TChateauCristalData", &fChateauCristalData);
}
