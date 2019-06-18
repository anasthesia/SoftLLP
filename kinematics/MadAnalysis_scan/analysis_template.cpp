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


// start here

  }
  return true;
}

