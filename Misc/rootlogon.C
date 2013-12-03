/*****************************************************************************
 * Copyright (C) 2009-2010   this file is part of the Ganil2Root Project     *
 *                                                                           *
 * For the licensing terms see $GANIL2ROOT/Licence                           *
 * For the list of contributors see $GANIL2ROOT/README/CREDITS               *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : 07/01/11                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: Example of rootlogon.C file which calls the Ganil2RootLogon.C *
 *             located in Ganil2Root/scripts and which loads all necessary   *
 *             Ganil2Root information needed by ROOT.                        *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
{
   // Load Ganil2RootLogon.C macro dealing with all the NPLib shared libraries
   TString path = gSystem->Getenv("GANIL2ROOT");
   gROOT->ProcessLine(Form(".x %s/scripts/Ganil2RootLogon.C+", path.Data()));
}
