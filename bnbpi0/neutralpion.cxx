#ifndef LARLITE_NEUTRALPION_CXX
#define LARLITE_NEUTRALPION_CXX

#include "neutralpion.h"

namespace larlite {

  bool neutralpion::initialize() {

        InitializeAnaTree();



    return true;
  }
  bool neutralpion::analyze(storage_manager* storage) {
	// Bring in the info for the event
        auto mctruth = storage->get_data<event_mctruth>("generator");
        auto mcnu = mctruth->at(0).GetNeutrino();
        auto mcpart = mctruth->at(0).GetParticles();

	//Fill out the neutrino interaction information
        ccnc = mcnu.CCNC();
        mode = mcnu.Mode();
        interaction = mcnu.InteractionType();
        w = mcnu.W();
        qsqr = mcnu.QSqr();

	// pi0count pair<(int) how many fsi pi0, (vector<int>) the track ID>
	auto pi0count = fBO.pi0count(mcpart);
	fsipi0 = pi0count.first;
	auto cmeson = fBO.cmesoncounter(mcpart);
	// protoncounter pair<(int) how many fsi protons, (vector<int>) the track ID>
	auto protoninfo = fBO.protoncounter(mcpart,ProtThresh);
	protoncount = protoninfo.first;

	if(pi0count.first==1 && cmeson==0){
		for(auto const mcp : mcpart){
			//find the particle info
			if(mcp.TrackId()==pi0count.second[0])
			{
                        auto traj = mcp.Trajectory();
			_spenergy = traj[0].E();
                        P_x = traj[0].X();
                        P_y = traj[0].Y();
                        P_z = traj[0].Z();
                        P_px = traj[0].Px();
                        P_py = traj[0].Py();
                        P_pz = traj[0].Pz();
			P_pmag = sqrt(P_px*P_px+P_py*P_py+ P_pz*P_pz);
			}// if we have the particle
		}//for loop over mcp
	}//if pi0 is single



  
	// Fill the FullTree
	FullTree->Fill();
	if(pi0count.first==1) SPTree->Fill();
    return true;
  }

  bool neutralpion::finalize() {
     if(_fout){
		FullTree->Write();
		SPTree->Write();
	      }
    return true;
  }

  void neutralpion::InitializeAnaTree()
        {
        FullTree = new TTree("FullTree","FullTree");
                FullTree->Branch("ccnc",&ccnc,"ccnc/I");
                FullTree->Branch("mode",&mode,"mode/I");
                FullTree->Branch("interaction",&interaction,"interaction/I");
                FullTree->Branch("w",&w,"w/D");
                FullTree->Branch("qsqr",&qsqr,"qsqr/D");
                FullTree->Branch("fsipi0",&fsipi0,"fsipi0/I");

        SPTree = new TTree("SPTree","SPTree");
                SPTree->Branch("ccnc",&ccnc,"ccnc/I");
                SPTree->Branch("mode",&mode,"mode/I");
                SPTree->Branch("interaction",&interaction,"interaction/I");
                SPTree->Branch("w",&w,"w/D");
                SPTree->Branch("qsqr",&qsqr,"qsqr/D");
                SPTree->Branch("fsipi0",&fsipi0,"fsipi0/I");
                SPTree->Branch("energy",&_spenergy,"spenergy/D");
                SPTree->Branch("PposX",&P_x,"P_x/D");
                SPTree->Branch("PposY",&P_y,"P_y/D");
                SPTree->Branch("PposZ",&P_z,"P_z/D");
                SPTree->Branch("PdirX",&P_px,"P_px/D");
                SPTree->Branch("PdirY",&P_py,"P_py/D");
                SPTree->Branch("PdirZ",&P_pz,"P_pz/D");
                SPTree->Branch("Ppmag",&P_pmag,"P_pmag/D");
                SPTree->Branch("protoncount",&protoncount,"protoncount/I");
	}

}
#endif
