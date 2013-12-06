// This macro converts a single run producing a ROOT output file
// with user class format
{
  gROOT->Reset(); 
  
  TString GRUpath = gSystem->Getenv("GRUDIR");
  gROOT->ProcessLine(Form(".include %s/include", GRUpath.Data()));
  gROOT->ProcessLine(".L ./GUser_convert.C++O"); // load and compile GUser class 
 
//  GTape *file = new GTape("./run_0220.dat.15Apr09_04h32m35s");
  GTape *file = new GTape("./run_54.dat.08Sep10_14h10m19s");
  file->Open();

  GUser * a= new GUser(file); 
  a->EventInit();
  a->SetSpectraMode(1); 
  a->SetUserMode(1);
  file->Rewind();
  
  a->SetTTreeMode(3, "./test.root");
  cout << "======== Debug START DoRun() =========" << endl;
  a->DoRun();
  cout << "======== Debug END DoRun() =========" << endl;
  
  file->Close();
  a->EndUser();                       // must be explicitly called , if it needs
  delete (a);                         // finish 

  // gROOT->ProcessLine(".q");
}
