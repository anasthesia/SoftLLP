#include "SampleAnalyzer/User/Analyzer/debug_distributions.h"
#include <fstream>
using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool debug_distributions::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;
  // initialize variables, histos
  //
  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void debug_distributions::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  //Manager()->Draw();
  // saving histos
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool debug_distributions::Execute(SampleFormat& sample, const EventFormat& event)
{
  // ***************************************************************************
  // Example of analysis with generated particles
  // Concerned samples : LHE/STDHEP/HEPMC
  // ***************************************************************************
  /*
  if (event.mc()==0)
  {
      return true;
  }
  */
    vector<const MCParticleFormat*> listInvisible;
    //cout << "---------------NEW EVENT-------------------" << endl;
    //
    MAfloat32 __event_weight__ = 1.0;
    if (weighted_events_ && event.mc()!=0) __event_weight__ = event.mc()->weight();
                                                                             
    if (sample.mc()!=0) sample.mc()->addWeightedEvents(__event_weight__);
    if (sample.mc()==0) cout << "zero weight" << endl;
    Manager()->InitializeForNewEvent(__event_weight__);
    
    MCParticleFormat lplus, lminus, eplus, eminus, muplus, muminus, nu, nue, psil;

    MALorentzVector plplus, plminus, pvisible, peplus, peminus, pmuplus, pmuminus;
    
    ParticleBaseFormat plnu, pee, pmumu, pll;

    for (MAuint32 i=0;i<event.mc()->particles().size();i++)
    {
        const MCParticleFormat* part=&(event.mc()->particles()[i]);
     
    // check if final state particle
        if (!PHYSICS->Id->IsFinalState(part)) continue;
    // muon selection based on PDG-id
        if ((part->pdgid() == 13)||(part->pdgid() == 11)) {
            lminus = *part;
            continue;
        }
        if ((part->pdgid() == -13)||(part->pdgid() == -11)) {
            lplus = *part;
            continue;
        }
        /*
        if (part->pdgid() == 11) {
            eminus = *part;
            //continue;
        }
        if (part->pdgid() == 13) {
            muminus = *part;
            //continue;
        }
        if (part->pdgid() == -11) {
            eplus = *part;
            //continue;
        }
        if (part->pdgid() == -13) {
            muplus = *part;
            //continue;
        }
        */
        if  ((part->pdgid() == 12)||(part->pdgid() == 14)) {
            nu = *part;
            continue;
        }
        /*
        if  (part->pdgid() == 12) {     
            nue = *part;
            //continue;
        }
        */
        if (part->pdgid() == 9000005) {
            psil = *part;

            continue;    

    }

    //cout<<muplus<<endl;

    plplus=lplus.momentum();
    plminus=lminus.momentum();
    //peminus=eminus.momentum();
    //pmuminus=muminus.momentum();
    //peplus=eplus.momentum();
    //pmuplus=muplus.momentum();
    pvisible=plplus+plminus;
    plnu=nu.momentum()+plplus;
    pll=plplus+plminus;
    //pmumu=pmuplus+pmuminus;


    ofstream f1("../Output/pTl_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f1 << lplus.pt()<< endl;
    f1.close();

    ofstream f2("../Output/pTnu_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app); 
    f2 << nu.pt()<< endl;
    f2.close();

    ofstream f3("../Output/pTpsil_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f3 << psil.pt()<< endl;
    f3.close();
    

    ofstream f4("../Output/pTvisible_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f4 << pvisible.Pt()<< endl;                          
    f4.close();

    ofstream f5("../Output/pnu_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f5 << nu.p()<< endl;
    f5.close();

    ofstream f6("../Output/langle_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f6 << lplus.angle(lminus)<< endl;
    f6.close();

    ofstream f7("../Output/dphi_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f7 << lplus.dphi_0_pi(lminus)<< endl;
    f7.close();

    ofstream f8("../Output/theta-lMET_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f8 << lplus.angle(-pvisible)<< endl;
    f8.close();

    ofstream f9("../Output/m-lnu_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f9 << plnu.m()<< endl;
    f9.close();
/*
    ofstream f10("../Output/theta_ll_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f10 << muplus.angle(muminus)<< endl;
    f10.close();

    ofstream f11("../Output/m-ee_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f11 << pee.m()<< endl;
    f11.close();
*/
    ofstream f12("../Output/m-ll_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f12 << pll.m()<< endl;
    f12.close();

    ofstream f13("../Output/dphi-lMET_rr5.00e-08_mS4.00e+02_mT4.20e+02.dat", fstream::app);
    f13 << lplus.dphi_0_pi(-pvisible)<< endl;
    f13.close();

  }
  return true;
}

