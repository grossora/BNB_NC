#ifndef BOTTLEOPENER_CXX
#define BOTTLEOPENER_CXX

#include "bottleopener.h"

        std::pair<int,std::vector<int>> bottleopener::pi0count(std::vector<larlite::mcpart> &parts){
        int total=0;
        std::vector<int> trackid;
        for(auto const& p : parts){
        if(p.PdgCode()==111 && p.StatusCode()==1){
                total+=1;
                trackid.push_back(p.TrackId());
                        }
                }// for loop over partiles
        std::pair<int,std::vector<int>> temp(total,trackid);
        return temp;
        }// pi0count


	int bottleopener::cmesoncounter(std::vector<larlite::mcpart> &parts){
        int cmeson = 0 ;
        for(auto const& p : parts){
                if(abs(p.PdgCode())==211 && p.StatusCode()==1) cmeson+=1;
		}
        return cmeson;
        }// cmeson counter



#endif
