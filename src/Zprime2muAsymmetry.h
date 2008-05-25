#ifndef ZP2MUASYM_H
#define ZP2MUASYM_H

#include <string>

#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SUSYBSMAnalysis/Zprime2muAnalysis/src/AsymFitData.h"
#include "SUSYBSMAnalysis/Zprime2muAnalysis/src/TFMultiD.h"
#include "SUSYBSMAnalysis/Zprime2muAnalysis/src/Zprime2muAnalysis.h"

const int FIT_ARRAY_SIZE = 50000;// max size of arrays for unbinned fits. 

class Zprime2muAsymmetry : public Zprime2muAnalysis {
 public:
  explicit Zprime2muAsymmetry(const edm::ParameterSet&);
  ~Zprime2muAsymmetry();

  void beginJob(const edm::EventSetup&);
  void analyze(const edm::Event&, const edm::EventSetup&);
  void endJob();

 private:
  static const double nSigma;
  static const unsigned int nNormPoints;
  static const unsigned int nSmearPoints;

  enum FITTYPE { ASYM, GRAV, GRAV_QQBAR, GRAV_GG, GRAV_THEORY };

  void bookFrameHistos();
  void bookFitHistos();

  void makeFakeData(int nEvents, double A_FB, double b);
  void smearGenData(const AsymFitData& data);

  double calcAFBError(double f, double b);
  void calcAsymmetry(double f, double b, double& A_FB, double& e_A_FB);
  void calcAsymmetry(const TH1F* h_cos, double& A_FB, double& e_A_FB);
  void calcAsymmetry(const TH1F* IdF, const TH1F* IdB, TH1F* IdA,
		     fstream& out);

  void calcFrameAsym();
  void fillFrameHistos();

  void fillFitData(const edm::Event& event);
  void dumpFitData();

  bool computeFitQuantities(const reco::CandidateCollection&, 
			    int eventNum, AsymFitData& data);

  void bookParamHistos();
  void fillParamHistos(bool fakeData);
  void getAsymParams();

  TFMultiD* getNewFitFcn(int fitType);
  void evalLikelihoods();
  void fitAsymmetry();

  void fitCosCS(TH1F* cos_hist, int params);
  void drawFrameHistos();
  void drawFitHistos();

  void deleteHistos();

  std::string print(const reco::Candidate& par) const;

  // store the event number so we don't have to get it from the edm
  // object every time
  int eventNum;
  TH1F *h_genCosNoCut;
  TH2F *AsymFitSmearHisto[6];
  TH1F *AsymFitHistoGen[6], *AsymFitHistoRec[6], *AsymFitSmearHistoDif[6];
  TH1F *AsymFitHistoGenSmeared[6];
  // look at the angular distributions separately by type
  TH1F *AsymFitHistoGenByType[2][6], *AsymFitHistoRecByType[2][6];

  TH1F *cosGJ[2][2], *cosCS[2][2];
  TH1F *cosBoost[2], *cosW[2];
  TH1F *cosCSRes;
  TH2F *rap_vs_cosCS[2], *rap3_vs_rap0;
  TH1F *FMassGJ[2][2], *FMassCS[2][2];
  TH1F *BMassGJ[2][2], *BMassCS[2][2];
  TH1F *AMassGJ[2][2], *AMassCS[2][2];
  TH1F *FMassBoost[2], *FMassW[2];
  TH1F *BMassBoost[2], *BMassW[2];
  TH1F *AMassBoost[2], *AMassW[2];
  TH1F *FRapGJ[2][2],  *FRapCS[2][2];
  TH1F *BRapGJ[2][2],  *BRapCS[2][2];
  TH1F *ARapGJ[2][2],  *ARapCS[2][2];
  TH1F *FRapBoost[2],  *FRapW[2];
  TH1F *BRapBoost[2],  *BRapW[2];
  TH1F *ARapBoost[2],  *ARapW[2];
  TH1F *FPseudGJ[2],   *FPseudCS[2];
  TH1F *BPseudGJ[2],   *BPseudCS[2];
  TH1F *FPseudBoost[2],*FPseudW[2];
  TH1F *BPseudBoost[2],*BPseudW[2];
  TProfile *cosCS3_diffsq_vs_cosCS0;
  TH1F *FMBoostCut[2][6];
  TH1F *BMBoostCut[2][6];
  TH1F *AsymMBoostCut[2][6];

  // histos used to get the mistag parameterizations
  TH1F *h_mass_dil[2];
  TH1F *h_rap_mistag, *h_rap_nomistag;
  TH1F *h_mistag[6][3];
  TH2F *h2_mistag[4];
  TH2F *h2_pTrap, *h2_pTrap_mistag;
  TH2F *h2_rap_cos_mistag, *h2_rap_cos_nomistag;
  TH2F *h2_rap_cos_p;
  TH1F *h_cos_mistag, *h_cos_cs, *h_cos_mistag_prob;
  TH1F *h_rap_dil[2], *h_pt_dil;
  TH1F *h_phi_cs;

  TH1F *h_cos_theta_true, *h_cos_theta_cs_acc;
  TH1F *h_cos_theta_cs, *h_cos_theta_cs_fixed;
  TH1F *h_cos_theta_cs_rec;
  TH1F *h_b_mass, *h_f_mass, *h_b_smass, *h_f_smass;
  TH1F *h_gen_sig[2];
  TH2F *h2_rap_cos_d[2];
  TH2F *h2_rap_cos_d_uncut[2];
  TH2F *h2_rap_cos_d_rec;
  TH1F *mistagProbEvents[3];

  // Data arrays for unbinned fits.  Fixed size arrays for now.
  // Order of the arrays: generated events, reconstructed events,
  //                      smeared generated events
  int nfit_used[3];   // number of events
  double pt_dil_data[3][FIT_ARRAY_SIZE];
  double phi_dil_data[3][FIT_ARRAY_SIZE];
  double mass_dil_data[3][FIT_ARRAY_SIZE];
  double rap_dil_data[3][FIT_ARRAY_SIZE];
  double cos_theta_cs_data[3][FIT_ARRAY_SIZE];
  double phi_cs_data[3][FIT_ARRAY_SIZE];
  // weights to keep track of which data point is from gg/qqbar
  double qqbar_weights[3][FIT_ARRAY_SIZE];
  double gg_weights[3][FIT_ARRAY_SIZE];

  // arrays for generating fake data from distributions
  double fake_cos_true[FIT_ARRAY_SIZE];
  double fake_cos_cs[FIT_ARRAY_SIZE];
  double fake_rap[FIT_ARRAY_SIZE];
  int fake_mistag_true[FIT_ARRAY_SIZE];
  int fake_mistag_cs[FIT_ARRAY_SIZE];

  std::vector<double> angDist;

  // config file parameters
  std::string outputFileBase;
  std::vector<std::string> genSampleFiles;
  double peakMass;
  bool onPeak;
  bool noFit;
  bool onlyEvalLLR;
  FITTYPE fitType;
  int numFits;
  int maxParamEvents;
  bool useCachedParams;
  std::string paramCacheFile;
  bool calcParamsOnly;
  bool internalBremOn;
  bool fixbIn1DFit;
  bool useCosTrueInFit;
  bool artificialCosCS;
};

#endif // ZP2MUASYM_H
