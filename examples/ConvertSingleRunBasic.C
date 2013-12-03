// This macro converts a single run producing a ROOT output file
// with user class format
{
  gROOT->Reset(); 
  
  TString GRUpath = gSystem->Getenv("GRUSYS");
  gROOT->ProcessLine(Form(".include %s/include", GRUpath.Data()));
//  gROOT->ProcessLine(".L ./GUser_convert.C++O"); // load and compile GUser class 
  gROOT->ProcessLine(".L ./GUser_convert_C.so"); // load and compile GUser class 
 
//  GTape *file = new GTape("/scratch/gypaos/data/testCOFEE/raw/run_0002.dat.13Apr12_14h09m19s");
//  GTape *file = new GTape("/scratch/gypaos/GanilData/e530/run/run_0363.dat.20Apr09_11h20m41s");
  GTape *file = new GTape("/scratch/gypaos/GanilData/e628/run_0005.dat.03Dec13_11h11m11s");
  file->Open();

  GUser * a= new GUser(file); 
  a->EventInit();
  a->SetSpectraMode(1); 
  a->SetUserMode(1);
  file->Rewind();
  
//  a->SetTTreeMode(1, "/scratch/gypaos/data/testCOFEE/root/run_0002_test.root");
  a->SetTTreeMode(3, "/scratch/gypaos/GanilData/e628/run_0005_test.root");
  cout << "======== Debug START DoRun() =========" << endl;
  a->DoRun();
  cout << "======== Debug END DoRun() =========" << endl;
  
  file->Close();
  a->EndUser();                       // must be explicitly called , if it needs
  delete (a);                         // finish 

  // gROOT->ProcessLine(".q");
}
