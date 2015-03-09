/**
 * \file bottleopener.h
 *
 * \ingroup bnbpi0
 * 
 * \brief Class def header for a class bottleopener
 *
 * @author ryan
 */

/** \addtogroup bnbpi0

    @{*/
#ifndef BOTTLEOPENER_H
#define BOTTLEOPENER_H

#include <iostream>

#include "DataFormat/mcpart.h"


/**
   \class bottleopener
   User defined class bottleopener ... these comments are used to generate
   doxygen documentation!
 */
class bottleopener{

public:

  /// Default constructor
  bottleopener(){}

  /// Default destructor
  ~bottleopener(){}

        std::pair<int,std::vector<int>> pi0count(std::vector<larlite::mcpart> &parts);
        int cmesoncounter(std::vector<larlite::mcpart> &parts);
        std::pair<int,std::vector<int>> protoncounter(std::vector<larlite::mcpart> &parts, double threshold);



};

#endif
/** @} */ // end of doxygen group 

