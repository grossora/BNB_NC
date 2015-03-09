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

	::bottleopener fBO;
	void InitializeAnaTree();

        TTree *FullTree;
        TTree *SPTree;

	// Variable 
	int ccnc;
	int mode;
	int interaction;
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
