/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPEVENTLISTENER_H_
#define _NUTI_MAPEVENTLISTENER_H_

#include "core/MapPos.h"

#include <vector>

namespace Nuti {
    class MapClickInfo;
    class VectorElementsClickInfo;
    
    /**
     * Listener for events like map and vector element clicks etc.
     */
    class MapEventListener {
    public:
        virtual ~MapEventListener() {}
    
        /**
         * Listener method that gets called when the map is panned, rotated, tilted or zoomed.
         * The thread this method is called from may vary.
         */
        virtual void onMapMoved() = 0;
    
        /**
         * Listener method that gets called when a click is performed on an empty area of the map.
         * This method will NOT be called from the main thread.
         * @param mapClickInfo A container that provides information about the click.
         */
        virtual void onMapClicked(const MapClickInfo& mapClickInfo) = 0;
    
        /**
         * Listener method that gets called when a click is performed on a vector element.
         * If there are multiple vector elements that are located at the click position, then the
         * results will be sorted by their distance to the camera. The closest element will be the first one
         * in the list. This method will NOT be called from the main thread.
         * @param vectorElementsClickInfo A container that provides information about the click.
         */
        virtual void onVectorElementClicked(const VectorElementsClickInfo& vectorElementsClickInfo) = 0;
    };
    
}

#endif
