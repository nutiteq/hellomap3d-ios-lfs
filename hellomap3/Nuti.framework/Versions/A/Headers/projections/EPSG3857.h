/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_EPSG3857_H_
#define _NUTI_EPSG3857_H_

#include "Projection.h"

namespace Nuti {

    /**
     * EPSG:3857 is a Spherical Mercator projection coordinate system popularized by web services such as Google and later OpenStreetMap.
     * Z-coordinate denotes height in meters.
     */
    class EPSG3857 : public Projection {
    public:
        EPSG3857();
        virtual ~EPSG3857();
        
        virtual double fromInternalScale(double size) const;
        virtual double toInternalScale(double meters) const;
    
        virtual MapPos fromWgs84(const MapPos& wgs84Pos) const;
        virtual MapPos toWgs84(const MapPos& mapPos) const;
        virtual std::string getName() const;
        
    private:
        static const int EARTH_RADIUS = 6378137;
        static const double HALF_EARTH_RADIUS;
        
        static const double DEGREES_90_IN_RAD;
        
        static const double METERS_TO_INTERNAL_EQUATOR;
    };
    
}

#endif
