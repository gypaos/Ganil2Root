// This macro converts a single run producing a ROOT output file
// with user class format
{
  gROOT->Reset(); 
  
  TString GRUpath = gSystem->Getenv("GRUSYS");
  gROOT->ProcessLine(Form(".include %s/include", GRUpath.Data()));
  gROOT->ProcessLine(".L ./GUser_convert.C++O"); // load and compile GUser class 
 
  GTape *file = new GTape("/scratch/gypaos/data/testCOFEE/raw/run_0002.dat.13Apr12_14h09m19s");
  file->Open();

  GUser * a= new GUser(file); 
  a->EventInit();
  a->SetSpectraMode(1); 
  a->SetUserMode(1);
  file->Rewind();
  
  a->SetTTreeMode(1, "/scratch/gypaos/data/testCOFEE/root/run_0002.root");
  cout << "======== Debug START DoRun() =========" << endl;
  a->DoRun();
  cout << "======== Debug END DoRun() =========" << endl;
  
  file->Close();
  a->EndUser();                       // must be explicitly called , if it needs
  delete (a);                         // finish 

  // gROOT->ProcessLine(".q");
}
