
// File and Version Information:
//      $Id: NDimUnfolding.h 2021-10-10 shlee@bnl.gov $
//
// Description:
//
// Authors: Sookhyun Lee <shlee@bnl.gov> 
//
//==============================================================================

#ifndef NDIMUNFOLDING_HH
#define NDIMUNFOLDING_HH

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TNamed.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,0,0)
#include "TVectorDfwd.h"
#include "TMatrixDfwd.h"
#else
class TVectorD;
class TMatrixD;
#endif
#endif

#if ((defined(__CINT__) && !defined(__MAKECINT__)) || defined(MAKEBUILD)) && !defined(NOTUNFOLD)
#define USE_TUNFOLD_H 1   // can include TUnfold.h (don't know for ACLiC)
#endif

#ifdef __CINT__
#include "TPad.h"    // Why is this necessary (at least in ROOT 5.18+)?
#include "ArgVars.h"
#else
class ArgVars;
#endif

class TFile;
class TCanvas;
class TPostScript;
class TLegend;
class TH1;
class TH2;
class TH3;
class TH1D;
class TH2D;
class TH3D;
class TF1;
class TNtuple;
class TTree;
class RooUnfoldResponse;
class RooUnfold;
class RooUnfoldErrors;
class RooUnfoldParms;

class NDimUnfolding : public TNamed {
public:
  // Parameters
  // default
  Int_t    method, stage, ftrainx1, ftestx1, ntx1, ntest, ntrain, wpaper, hpaper, regmethod;
  Int_t    ntoyssvd, nmx1, onepage, doerror, dim, overflow, addbias, nbPDF, verbose, dodraw, dosys;
  Int_t    ntoys, ploterrors, plotparms, doeff, addfakes, seed, dofit;
  Double_t x1lo, x1hi, mtrainx1, wtrainx1, btrainx1, mtestx1, wtestx1, btestx1, mscalex1, bincorr;
  Double_t regparm, effx1lo, effx1hi, x1bias, x1smear, fakex1lo, fakex1hi, minparm, maxparm, stepsize;
  // 2d
  Int_t    ftrainx2, ftestx2, ntx2, nmx2;
  Double_t x2lo, x2hi, mtrainx2, wtrainx2, btrainx2, mtestx2, wtestx2, btestx2, mscalex2;
  Double_t effx2lo, effx2hi, fakex2lo, fakex2hi, rotx1x2, x2bias, x2smear;
  // 3d
  Int_t    ftrainx3, ftestx3, ntx3, nmx3;
  Double_t x3lo, x3hi, mtrainx3, wtrainx3, btrainx3, mtestx3, wtestx3, btestx3, mscalex3;
  Double_t effx3lo, effx3hi, fakex3lo, fakex3hi, rotx1x3, rotx2x3, x3bias, x3smear;

  Float_t x1t, x2t, x3t, x1,x2,x3,x1m, x2m, x3m;
  TString  setname, rootfile;
  TString inmc, indata;
  TString varnamex1, varnamex2, varnamex3;
  Bool_t do_closure_test;

  // Data
  TFile	     	     *tfMC, *tfData;
  TTree              *ttMC, *ttData;
  Int_t              error, ipad, ntbins, nmbins;
  TCanvas*           canvas;
  TPostScript*       ps;
  TLegend            *lTrain, *lTest, *lErrors;
  TH1                *hTrain, *hTrainTrue, *hTrainFake, *hTrue, *hMeas, *hReco, *hFake, *hRes, *hPulls;
  TH1D *hTrainX1, *hTrainTrueX1, *hTrainFakeX1, *hTrueX1, *hMeasX1, *hRecoX1, *hFakeX1, *hPullsX1;
  TH1D *hTrainX2, *hTrainTrueX2, *hTrainFakeX2, *hTrueX2, *hMeasX2, *hRecoX2, *hFakeX2, *hPullsX2;
  TH1D *hTrainX3, *hTrainTrueX3, *hTrainFakeX3, *hTrueX3, *hMeasX3, *hRecoX3, *hFakeX3, *hPullsX3;
  TH1                *hUnfErr, *hToyErr, *hParmChi2, *hParmErr, *hParmRes, *hParmRms;
  TH2D               *hResmat, *hCorr, *hMeasCorr;
  TH2D  	     *hTrainTrueX1X2, *hTrainTrueX2X3, *hTrainTrueX1X3, *hTrueX1X2, *hTrueX2X3, *hTrueX1X3;
  TH2D 		     *hMeasX1X2, *hMeasX2X3, *hMeasX1X3, *hRecoX1X2, *hRecoX2X3, *hRecoX1X3;
  TH2D		     *hPullsX1X2,*hPullsX2X3,*hPullsX1X3;
  TF1                *fitFunc, *trueFunc;
  TNtuple            *ntChi2;
  RooUnfoldResponse* response;
  RooUnfold*         unfold;
  RooUnfoldErrors*   errors;
  RooUnfoldParms*    parms;
  // Constructors
  NDimUnfolding (const char* name= "NDimUnfolding");
  NDimUnfolding (const char* name, const char* args);
  NDimUnfolding (const char* name, int argc, const char* const* argv);
  virtual ~NDimUnfolding();

  // Methods and functions
  virtual void     Parms (ArgVars& args);
  virtual Int_t    Run();
  virtual void     SetupCanvas();
  virtual Int_t    RunTests();
  virtual Int_t    Train();
  virtual void     TrainResults();
  virtual Int_t    Test();
  virtual void     SetMeasuredCov();
  virtual Int_t    Unfold();
  virtual void     Fit();
  virtual void     Results();
  virtual void     Results2D();
  virtual void     Results3D();
  virtual void     PlotErrors();
  virtual void     PlotParms();
  virtual TH1D*    Generate (TVectorD& x, const char* name, const char* title, Int_t nt, Int_t fpdf,
                             Int_t nx, Double_t xlo, Double_t xhi, Double_t bkg, Double_t mean, Double_t width,
                             Double_t bias, Double_t smear);
  virtual Int_t    Fakes    (TVectorD& x, Int_t nm, Int_t nx, Double_t lo, Double_t hi, Double_t fakelo, Double_t fakehi) const;
  virtual bool     Eff      (Double_t x,           Double_t xlo, Double_t xhi, Double_t efflo, Double_t effhi) const;
  virtual Double_t Smear    (Double_t x, Int_t nt, Double_t xlo, Double_t xhi, Double_t bias,  Double_t smear) const;
  virtual Double_t Overflow (Double_t x, Int_t nt, Double_t xlo, Double_t xhi) const;
  virtual void     Reset();
  virtual void     SetDefaults();
  virtual int      SetArgs  (int argc, const char* const* argv, bool split= false);
  virtual void     Init();
  virtual void     SetMethod(Int_t method);
  virtual void     SetDimension(Int_t dim);
  virtual void     SetX1Name(const TString& x1nam);
  virtual void     SetX2Name(const TString& x2nam);
  virtual void     SetX3Name(const TString& x3nam);
  virtual void     SetNMeasuredBins(int var, int nbins);
  virtual void     SetBinsDefault();
  virtual void     SetClosureTest(Bool_t do_ct);

  virtual Int_t    CheckParms();
  virtual void     PrintParms (std::ostream& o) const;
  static  void     setmax   (TH1* h, const TH1* h1= 0, const TH1* h2= 0, const TH1* h3= 0,
                             const TH1* h4= 0, const TH1* h5= 0, const TH1* h6= 0);
  static  void     Legend (TLegend*& legend, TH1* truth, TH1* fake, TH1* meas, TH1* reco= 0, TF1* ff=0, TF1* tf=0);
  static  TH2D*    CorrelationHist (const TMatrixD& cov,
                                    const char* name="rho", const char* title="Correlation matrix",
                                    Double_t lo=0.0, Double_t hi=1.0);
  static TF1*      FitFunc (Int_t fpdf, TH1* h, Double_t mean= 0.0, Double_t width= 2.5, Double_t bkg= 0.0);
  
  // from 2D histograms
  static TH1D* ProjectionX (const TH1* h, const char* name="_px", const char* title=0, Option_t* opt="");
  static TH1D* ProjectionY (const TH1* h, const char* name="_py", const char* title=0, Option_t* opt="");
  // from 3D histograms
  static TH1D* Projection1D (const TH1* h, Option_t* xyz, const char* name=0, const char* title=0, Option_t* opt="");
  static TH2D* Projection2D (const TH1* h, Option_t* xyz, const char* name=0, const char* title=0, Option_t* opt="");
  static TH1D* ProjectionXFrom3D (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="")
  {return Projection1D(h,"x",name,title,opt);}
  static TH1D* ProjectionYFrom3D (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="")
  {return Projection1D(h,"y",name,title,opt);}
  static TH1D* ProjectionZFrom3D (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="")
  {return Projection1D(h,"z",name,title,opt);}
  static TH2D* ProjectionXYFrom3D (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="")
  {return Projection2D(h,"xy",name,title,opt);}
  static TH2D* ProjectionYZFrom3D (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="")
  {return Projection2D(h,"yz",name,title,opt);}
  static TH2D* ProjectionXZFrom3D (const TH1* h, const char* name=0, const char* title=0, Option_t* opt="")
  {return Projection2D(h,"xz",name,title,opt);}


  Int_t Fill (TH1* h, Double_t x) {TH1* h1= dynamic_cast<TH1*>(h); return h1->Fill(x);}
  Int_t Fill (TH1* h, Double_t x, Double_t y) {TH2* h2= dynamic_cast<TH2*>(h); return h2->Fill(x,y);}
  Int_t Fill (TH1* h, Double_t x, Double_t y, Double_t z) {TH3* h3= dynamic_cast<TH3*>(h); return h3->Fill(x,y,z);}

protected:
  virtual int       GetDimension();
  virtual TString&  GetX1Name();
  virtual TString&  GetX2Name();
  virtual TString&  GetX3Name();
  virtual int       GetNMeasuredBins(int var);
  

};
#ifndef NOINLINE
#include "NDimUnfolding.icc"
#endif

#endif
