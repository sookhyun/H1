//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldTest.cxx 327 2011-11-18 02:03:46Z T.J.Adye $
//
// Description:
//      This is the main driver that performs the multidimensional unfolding procedure using 
//      MC data (Django/Rapgap) on the H1 data. The actual tests are performed using the
//      NDimUnfolding class.
//
// Author: Sookhyun Lee <sookhyun@umich.edu>
//
//==============================================================================

#include "NDimUnfolding.h"

NDimUnfolding* test= 0;

//==============================================================================
// Routine to run with parameters specified as a string
//==============================================================================

void NDimUnfold (const char* args= "")
{
// If run interactively, remove canvas and all histograms that might have been
// created with a previous invocation.
  delete test; test= 0;
  gDirectory->Clear();

 
  test= new NDimUnfolding ("NDimUnfolding", args);
  // available methods: RooUnfold::kNone,     RooUnfold::kBayes,   RooUnfold::kSVD 
  //                    RooUnfold::kBinByBin, RooUnfold::kTUnfold, RooUnfold::kInvert, RooUnfold::kIDS
  test->SetMethod(RooUnfold::kBayes);
  test->SetX1Name("tau1b");
  test->SetX2Name("tau_zQ");// x_is, x_e, x_ml (?) 
  test->SetX3Name("G1J_e_05");// Q2_is, Q2_e, Q2_ml (?)
  test->SetDimension(2);
  test->SetBinsDefault();
  test->SetClosureTest(true);
  test->Run();
}

#ifndef __CINT__

//==============================================================================
// Main program when run stand-alone
//==============================================================================

int main (int argc, char** argv) {
  NDimUnfolding maintest ("NDimUnfolding", argc, argv);
  return maintest.Run();
}

#endif
