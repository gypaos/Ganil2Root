#include "TSystem.h"
#include "TROOT.h"
#include "GUser.h"
#include "GUnitServerRoot.h"

void ConvertSingle(){  
  // specify good include dir!
  gROOT->Reset(); 
  

  char command[100];
  gROOT->ProcessLine(command);
  gSystem->Load("GUser.so"); //load and compile GUser class

  GTape *file = new GTape("/home/muvi/e748_run/run_0002.dat.13-06-17_09h03m29s");
  //GTape *file = new GTape("/data/tiara/e628/run/run_1231.dat.25Feb14_23h37m42s.1.gz");
  file->Open();                          // Open Device
  GUser * a= new GUser(file);            // creat user treatement environement
  GNetServerRoot *serv = new GNetServerRoot(9090, a);
  a->EventInit();                        // event initialisation
  a->SetSpectraMode(0);                  // Declare all raw parameters as histograms
  a->SetTTreeMode (TREE_USER,"./runstd.root");   // Do a standart TTree ( one leaf  for each parameter) of events
  serv->StartServer();
  a->InitUser();     // Do Init User()
  //cout  <<  "  hello " << endl;   
  file->Rewind();        // rewind run
  a->DoRun();
  file->Close();

  a->EndUser();              // must be explicitly called , if it needs
  a->SpeSave("histo.root"); // save all declared histogram 
  delete (a);   // finish 
  gROOT->ProcessLine(".q");
}


