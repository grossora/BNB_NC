#ifndef LARLITE_NCPIZEROSORTER_CXX
#define LARLITE_NCPIZEROSORTER_CXX

#include "ncpizerosorter.h"

namespace larlite {

  bool ncpizerosorter::initialize() {

    //

    return true;
  }
  
  bool ncpizerosorter::analyze(storage_manager* storage) {
    // bring in the truth and particles
        auto mctruth = storage->get_data<event_mctruth>("generator");
        auto mcnu = mctruth->at(0).GetNeutrino();
        auto mcpart = mctruth->at(0).GetParticles();
//        auto mcshower = storage->get_data<event_mcshower>("mcreco");

    // some basics
        ccnc = mcnu.CCNC();

///// finding the mother info 

for(unsigned int a = 0 ; a<mcpart.size(); a++){

	// print out the particle info 
	std::cout<<" particle info"<<mcpart.at(a).PdgCode()<<std::endl;
	}


    // pi0count pair<(int) how many fsi pi0, (vector<int>) the track ID>
        auto pi0count = fBO.pi0count(mcpart);
//        fsipi0 = pi0count.first;
        auto cmeson = fBO.cmesoncounter(mcpart);

	totalcount++;
	if(ccnc==1 && pi0count.first==1 && cmeson==0){
	sigcount++;
	return true;
	}

	return false;

//print out some stuff 
//if(ccnc==1&& pi0count.first>0){
//std::cout<<" num pions "<< pi0count.first<<std::endl;
//std::cout<<" num cmeson "<< cmeson<<std::endl;
//	}

  }

  bool ncpizerosorter::finalize() {
	std::cout<<"Summary Log: \n\tPassing events : "<< sigcount
	<<"\n\tTotal events: "<<totalcount
	<<"\n\tSignal "<<(double)sigcount/totalcount<<std::endl;


  
    return true;
  }

}
#endif
