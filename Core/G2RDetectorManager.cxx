#include "G2RDetectorManager.h"
#include "G2RModularLabel.h"
#include "G2RDetectorFactory.h"
#include "NPVDetector.h"
#include <cstdlib>
using namespace std;



///////////////////////////////////////////////////////////////////////////////
G2R::DetectorManager::DetectorManager(){
  fModularLabel = new G2R::ModularLabel;
  fModularLabel->LoadLabel("ModularLabel.txt");
fLabelToDetector.clear();
}

///////////////////////////////////////////////////////////////////////////////
G2R::DetectorManager::~DetectorManager(){
  map<string,G2R::VDetector*>::iterator it;

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {  
    delete it->second;
  }
  fDetectorMap.clear();
  delete fModularLabel;
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
  if(it==fLabelToDetector.end())
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
}

///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Init(DataParameters* g){
  map<string,G2R::VDetector*>::iterator it;
  bool result = true;
  fModularLabel->Init(g);

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    it->second->Init(g);
  }
  return result;
}

///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Is(unsigned short label,unsigned short value){

  static map<unsigned short,string>::iterator it;
  it=fLabelToDetector.find(label);
  if(it!=fLabelToDetector.end()){
    fDetectorMap[it->second]->Is(label,value);
}
  return true; 
 
 /*map<string,G2R::VDetector*>::iterator it;

  
  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    it->second->Is(label,value);
  }
  fModularLabel->Is(label,value);
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
  fModularLabel->Clear();

  return result;
}

///////////////////////////////////////////////////////////////////////////////
void G2R::DetectorManager::InitBranch(TTree* tree){
  map<string,G2R::VDetector*>::iterator it;

  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
    it->second->InitBranch(tree);
  }
  fModularLabel->InitBranch(tree);
}
///////////////////////////////////////////////////////////////////////////////
bool G2R::DetectorManager::Treat(){
  fModularLabel->Treat();
  return true;
}

///////////////////////////////////////////////////////////////////////////////
void G2R::DetectorManager::SetRawDataPointer(NPL::DetectorManager* NPDetectorManager){
  map<string,G2R::VDetector*>::iterator it;
 
  for (it=fDetectorMap.begin(); it!=fDetectorMap.end(); it++) {
   NPL::VDetector* det = NPDetectorManager->GetDetector(it->first);
    det->SetRawDataPointer(it->second->GetData());
    }

   TModularLeafPhysics* Modular = (TModularLeafPhysics*) (NPDetectorManager->GetDetector("ModularLeaf"));
   if(Modular)
    fModularLabel->SetModularLeafPointer(Modular);

}

