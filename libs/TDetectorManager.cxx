#include"TDetectorManager.h"
#include "TModularLabel.h"
#include "TMust2.h"  
#include "TCATS.h"
#include "TExogam.h"  
#include "TTrigger.h" 
#include "TTac.h" 
#include "TPlastic.h" 
#include "TSiLi.h" 
#include "TSiRes.h" 
#include "TLaBr3.h" 
#include "TLise.h" 
#include "TTiaraHyball.h" 
#include "TTiaraBarrel.h"  
#include "TCharissa.h" 
using namespace G2R;

#include<cstdlib>
///////////////////////////////////////////////////////////////////////////////
TDetectorManager::TDetectorManager(){
}

///////////////////////////////////////////////////////////////////////////////
TDetectorManager::~TDetectorManager(){

  map<string,TDetector*>::iterator it;

  for(it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++){  
    delete it->second;
  }

  fDetectorMap.clear();

}

///////////////////////////////////////////////////////////////////////////////
TDetector* TDetectorManager::GetDetector(string DetectorName){
  map<string,TDetector*>::iterator det = fDetectorMap.find(DetectorName);

  if(det!=fDetectorMap.end()) return det->second;
  else{
    cout << "ERROR: Detector " << DetectorName 
      << " Does not exist in TDetectorManager " << endl;
    exit(1);
  }
}
///////////////////////////////////////////////////////////////////////////////
void TDetectorManager::AddDetector(string DetectorName){

  if(DetectorName=="ModularLabel"){
    TDetector* det = new TModularLabel();
    fDetectorMap["ModularLabel"] = det;
  }

  else if(DetectorName=="MUST2"){
    TDetector* det = new TMust2();
    fDetectorMap["MUST2"] = det;
  }

  else if(DetectorName=="CATS"){
    TDetector* det = new TCATS();
    fDetectorMap["CATS"] = det;
  }
  else if(DetectorName=="EXOGAM"){
    TDetector* det = new TExogam();
    fDetectorMap["EXOGAM"] = det;
  }
  else if(DetectorName=="Charissa"){
    TDetector* det = new TCharissa();
    fDetectorMap["Charissa"] = det;
  }
  else if(DetectorName=="TiaraBarrel"){
    TDetector* det = new TTiaraBarrel();
    fDetectorMap["TiaraBarrel"] = det;
  }
  else if(DetectorName=="TiaraHyball"){
    TDetector* det = new TTiaraHyball();
    fDetectorMap["TiaraHyball"] = det;
  }
  else if(DetectorName=="TAC"){
    TDetector* det = new TTac();
    fDetectorMap["TAC"] = det;
  }
  else if(DetectorName=="Trigger"){
    TDetector* det = new TTrigger();
    fDetectorMap["Trigger"] = det;
  }
  else if(DetectorName=="Plastic"){
    TDetector* det = new TPlastic();
    fDetectorMap["Plastic"] = det;
  }
  else if(DetectorName=="SiLi"){
    TDetector* det = new TSiLi();
    fDetectorMap["SiLi"] = det;
  }
  else if(DetectorName=="SiRes"){
    TDetector* det = new TSiRes();
    fDetectorMap["SiRes"] = det;
  }
  else if(DetectorName=="LaBr3"){
    TDetector* det = new TLaBr3();
    fDetectorMap["LaBr3"] = det;
  }
  else if(DetectorName=="Lise"){
    TDetector* det = new TLise();
    fDetectorMap["Lise"] = det;
  }

}

///////////////////////////////////////////////////////////////////////////////
bool TDetectorManager::Init(GDataParameters* g){
  map<string,TDetector*>::iterator it;
  bool result = true;

  for(it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++){
    it->second->Init(g);
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////
bool TDetectorManager::Is(UShort_t label,Short_t value){
  map<string,TDetector*>::iterator it;

  for(it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++){
    if(it->second->Is(label,value)){
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
bool TDetectorManager::Clear(){
  map<string,TDetector*>::iterator it;
  bool result = true;

  for(it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++){
    result = result && it->second->Clear();
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////
void TDetectorManager::InitBranch(TTree* tree){
  map<string,TDetector*>::iterator it;

  for(it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++){
    it->second->InitBranch(tree);
  }
}

