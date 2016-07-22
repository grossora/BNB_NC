/**
 * \file ncpizerosorter.h
 *
 * \ingroup bnbpi0
 * 
 * \brief Class def header for a class ncpizerosorter
 *
 * @author grossora
 */

/** \addtogroup bnbpi0

    @{*/

#ifndef LARLITE_NCPIZEROSORTER_H
#define LARLITE_NCPIZEROSORTER_H

#include "Analysis/ana_base.h"
#include "bottleopener.h"

#include "DataFormat/mctruth.h"
#include "DataFormat/mcpart.h"
#include "DataFormat/mcshower.h"



namespace larlite {
  /**
     \class ncpizerosorter
     User custom analysis class made by SHELL_USER_NAME
   */
  class ncpizerosorter : public ana_base{
  
  public:

    /// Default constructor
    ncpizerosorter(){ _name="ncpizerosorter"; _fout=0;}

    /// Default destructor
    virtual ~ncpizerosorter(){}

    /** IMPLEMENT in ncpizerosorter.cc!
        Initialization method to be called before the analysis event loop.
    */ 
    virtual bool initialize();

    /** IMPLEMENT in ncpizerosorter.cc! 
        Analyze a data event-by-event  
    */
    virtual bool analyze(storage_manager* storage);

    /** IMPLEMENT in ncpizerosorter.cc! 
        Finalize method to be called after all events processed.
    */
    virtual bool finalize();

  protected:

        ::bottleopener fBO;

    
        int ccnc;
        int mode;
        int interaction;
        int status = -999;
        double w;
        double qsqr;
        int fsipi0;
        double _spenergy;
	double sigcount;
	int totalcount;



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
