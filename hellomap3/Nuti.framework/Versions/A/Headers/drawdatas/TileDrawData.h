/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TILEDRAWDATA_H_
#define _NUTI_TILEDRAWDATA_H_

namespace Nuti {

    class TileDrawData {
    public:
        TileDrawData(long long tileId, bool preloadingTile);
        virtual ~TileDrawData();
        
        float getAlpha() const;
        void setAlpha(float alpha);
        
        bool isPreloadingTile() const;
    
        long long getTileId() const;
    
    private:
        float _alpha;
        
        bool _preloadingTile;
        
        long long _tileId;
    
    };
    
}

#endif
