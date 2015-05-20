/**
 * \file neutralpion.h
 *
 * \ingroup bnbpi0
 * 
 * \brief Class def header for a class neutralpion
 *
 * @author ryan
 */

/** \addtogroup bnbpi0

    @{*/

#ifndef LARLITE_NEUTRALPION_H
#define LARLITE_NEUTRALPION_H

#include "Analysis/ana_base.h"

#include "bottleopener.h"

#include "DataFormat/mctruth.h"
#include "DataFormat/mcpart.h"
#include "DataFormat/mcshower.h"


namespace larlite {
  /**
     \class neutralpion
     User custom analysis class made by SHELL_USER_NAME
   */
  class neutralpion : public ana_base{
  
  public:

    /// Default constructor
    neutralpion(){ _name="neutralpion"; _fout=0;}

    /// Default destructor
    virtual ~neutralpion(){}

    /** IMPLEMENT in neutralpion.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in neutralpion.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in neutralpion.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

  protected:
	
	double ProtThresh = 0.20;// Based on Argoneut
	
	::bottleopener fBO;
	void InitializeAnaTree();

        TTree *FullTree;
        TTree *SPTree;
        TTree *SP_Gamma_Tree;

	// Variable 
	int ccnc;
	int mode;
	int interaction;
	int status = -999;
	double w; 
	double qsqr;
	int fsipi0;
	double _spenergy;

	double P_x;
	double P_y;
	double P_z;
	double P_px;
	double P_py;
	double P_pz;
	double P_pmag;
	int protoncount;


        double contain_shower_a = -999;
        double contain_shower_b = -999;


        double shower_a_E = -999;
        double shower_a_x = -999;
        double shower_a_y = -999;
        double shower_a_z = -999;
        double shower_a_px = -999;
        double shower_a_py = -999;
        double shower_a_pz = -999;
        double shower_b_E = -999;
        double shower_b_x = -999;
        double shower_b_y = -999;
        double shower_b_z = -999;
        double shower_b_px = -999;
        double shower_b_py = -999;
        double shower_b_pz = -999;

        double sprof_a_E = -999;
        double sprof_a_x = -999;
        double sprof_a_y = -999;
        double sprof_a_z = -999;
        double sprof_a_px = -999;
        double sprof_a_py = -999;
        double sprof_a_pz = -999;
        double sprof_b_E = -999;
        double sprof_b_x = -999;
        double sprof_b_y = -999;
        double sprof_b_z = -999;
        double sprof_b_px = -999;
        double sprof_b_py = -999;
        double sprof_b_pz = -999;



    
  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 
