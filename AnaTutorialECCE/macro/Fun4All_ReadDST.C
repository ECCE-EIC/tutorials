#ifndef MACRO_FUN4ALL_READDST_C
#define MACRO_FUN4ALL_READDST_C


#include <GlobalVariables.C>
#include <G4_Input.C>

#include <anatutorialecce/AnaTutorialECCE.h>

#include <TROOT.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllServer.h>

#include <phool/recoConsts.h>


R__LOAD_LIBRARY(libfun4all.so)
// Use libg4eicdst for campaign 2 DSTs
R__LOAD_LIBRARY(libg4eicdst.so)
// Use libg4dst for campaign 1 DSTs
//R__LOAD_LIBRARY(libg4dst.so)
R__LOAD_LIBRARY(libanatutorialecce.so)



int Fun4All_ReadDST(const int nEvents = 1,
		    const string& inputFile = "DST_SIDIS_pythia6_ep_18x100lowq2_005_1486000_02000.root",
		    const string &outputFile = "G4EICDetector.root")

{
  //---------------
  // Fun4All server
  //---------------
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(1);

  // just if we set some flags somewhere in this macro
  recoConsts *rc = recoConsts::instance();
  
  Enable::IP6 = true;

  Input::READHITS = true;
  INPUTREADHITS::filename[0] = inputFile;

  AnaTutorialECCE *anaTutorial = new AnaTutorialECCE("anaTutorial", outputFile + "_anaTutorial.root");
  anaTutorial->setMinJetPt(3.);
  anaTutorial->Verbosity(0);
  anaTutorial->analyzeTracks(true);
  anaTutorial->analyzeClusters(true);
  anaTutorial->analyzeJets(true);
  anaTutorial->analyzeTruth(false);
  se->registerSubsystem(anaTutorial);

  InputManagers();

  se->run(nEvents);

  se->End();
  
  delete se;
  std::cout << "All done processing" << std::endl;
  gSystem->Exit(0);
  return 0;

}
#endif
