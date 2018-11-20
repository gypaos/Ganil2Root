#include "G2RDetectorManager.h"
#include "G2RModularLabel.h"
#include "G2RDetectorFactory.h"
#include "NPVDetector.h"
#include <cstdlib>
using namespace std;



///////////////////////////////////////////////////////////////////////////////
G2R::DetectorManager::DetectorManager(){
}

///////////////////////////////////////////////////////////////////////////////
G2R::DetectorManager::~DetectorManager(){
  map<string,G2R::VDetector*>::iterator it;

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {  
    delete it->second;
  }

  fDetectorMap.clear();
}

///////////////////////////////////////////////////////////////////////////////
G2R::VDetector* G2R::DetectorManager::GetDetector(string DetectorName){
  map<string,G2R::VDetector*>::iterator det = fDetectorMap.find(DetectorName);

  if (det!=fDetectorMap.end()) return det->second;
  else {
    cout << "ERROR: Detector " << DetectorName 
      << " Does not exist in TDetectorManager " << endl;
    exit(1);
  }
}


////////////////////////////////////////////////////////////////////////////////
void G2R::DetectorManager::RegisterLabelToDetector(unsigned short label, string Detector){
  map<unsigned short,string>::iterator it;
  it=fLabelToDetector.find(label);
  if(it!=fLabelToDetector.end())
    fLabelToDetector[label]=Detector;
  else
    cout << "WARNING: label " << label << " is already associated with detector " << it->second << endl;  
  }
 
///////////////////////////////////////////////////////////////////////////////
void G2R::DetectorManager::AddDetector(string DetectorName){

  // Access the DetectorFactory and ask it to load the Class List from NPTool
  string classlist = getenv("NPTOOL");
  classlist += "/NPLib/ClassList.txt";
  G2R::DetectorFactory* theFactory = G2R::DetectorFactory::getInstance();
  theFactory->ReadClassList(classlist);

  G2R::VDetector* detector = theFactory->Construct(DetectorName);
  if(detector!=NULL){
      cout << "//// G2R Adding Detector " << DetectorName << endl; 
      fDetectorMap[DetectorName] = detector;     
      detector->SetDetectorManager(this);
  } 

/*  else if(DetectorName=="MUST2"){
    G2R::VDetector* det = new TMust2();
    fDetectorMap["MUST2"] = det;
  }

  else if(DetectorName=="CATS"){
    G2R::VDetector* det = new TCATS();
    fDetectorMap["CATS"] = det;
  }
  else if(DetectorName=="EXOGAM"){
    G2R::VDetector* det = new TExogam();
    fDetectorMap["EXOGAM"] = det;
  }
  else if(DetectorName=="Charissa"){
    G2R::VDetector* det = new TCharissa();
    fDetectorMap["Charissa"] = det;
  }
  else if(DetectorName=="TiaraBarrel"){
    G2R::VDetector* det = new TTiaraBarrel();
    fDetectorMap["TiaraBarrel"] = det;
  }
  else if(DetectorName=="TiaraHyball"){
    G2R::VDetector* det = new TTiaraHyball();
    fDetectorMap["TiaraHyball"] = det;
  }
  else if(DetectorName=="Trigger"){
    G2R::VDetector* det = new TTrigger();
    fDetectorMap["Trigger"] = det;
  }
  else if(DetectorName=="Plastic"){
    G2R::VDetector* det = new TPlastic();
    fDetectorMap["Plastic"] = det;
  }
  else if(DetectorName=="SiLi"){
    G2R::VDetector* det = new TSiLi();
    fDetectorMap["SiLi"] = det;
  }
  else if(DetectorName=="SiRes"){
    G2R::VDetector* det = new TSiRes();
    fDetectorMap["SiRes"] = det;
  }
  else if(DetectorName=="LaBr3"){
    G2R::VDetector* det = new TLaBr3();
    fDetectorMap["LaBr3"] = det;
  }
  else if(DetectorName=="Lise"){
    G2R::VDetector* det = new TLise();
    fDetectorMap["Lise"] = det;
  }
*/
}

///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Init(DataParameters* g){
  map<string,G2R::VDetector*>::iterator it;
  bool result = true;

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    it->second->Init(g);
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Is(UShort_t label,Short_t value){

  fDetectorMap[fLabelToDetector[label]]->Is(label,value);

  return true; 
 
 /*map<string,G2R::VDetector*>::iterator it;

  
  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    it->second->Is(label,value);
  }
  return false;
*/

}

///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Clear(){
  map<string,G2R::VDetector*>::iterator it;
  bool result = true;

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    result = result && it->second->Clear();
  }

  return result;
}

///////////////////////////////////////////////////////////////////////////////
void G2R::DetectorManager::InitBranch(TTree* tree){
  map<string,G2R::VDetector*>::iterator it;

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    it->second->InitBranch(tree);
  }
}
///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Treat(){
  return true;
}

///////////////////////////////////////////////////////////////////////////////
void G2R::DetectorManager::SetRawDataPointer(NPL::DetectorManager* NPDetectorManager){
  map<string,G2R::VDetector*>::iterator it;
 
  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
   NPL::VDetector* det = NPDetectorManager->GetDetector(it->first);
   det->SetRawDataPointer(it->second->GetData());
  } 
}

