/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PROJECTION_H_
#define _NUTI_PROJECTION_H_

#include "core/MapPos.h"
#include "core/MapBounds.h"

namespace Nuti {
    
    /**
     * An abstract base class for all projections.
     */
    class Projection {
    public:
        virtual ~Projection();
    
        /**
         * Returns the actual class name of this vector element. This is used
         * for dynamically creating Java and ObjC proxy classes, because Swig can't automatically
         * generate child proxy classes from a base class pointer.
         * @return The class name of this vector element.
         */
        const std::string& getClassName() const;

        /**
         * Returns the bounds of this projection.
         * @return The bounds of this projection.
         */
        virtual MapBounds getBounds() const;
        
        /**
         * Returns local scale for the specified position.
         * @param pos The position in the internal coordinate system.
         * @return The local scale for the specified position.
         */
        virtual double getLocalScale(const MapPos& pos) const;
        
        /**
         * Converts meters to approximate internal size at the specified position, towards specified direction.
         * @param pos The position in the coordinate system of this projection.
         * @param dir The direction in which the the distance is calculated.
         * @param meters The meters.
         * @return The approximate size in internal coordinate system.
         */
        double toInternalScale(const MapPos& pos, const MapVec& dir, double meters) const;
        
        /**
         * Converts internal size to meters at the equator.
         * @param size The size in the internal coordinate system.
         * @return The approximate size in meters at the equator.
         */
        virtual double fromInternalScale(double size) const = 0;
        
        /**
         * Converts meters to approximate internal size at the equator.
         * @param meters The meters at the equator.
         * @return The approximate size in internal coordinate system.
         */
        virtual double toInternalScale(double meters) const = 0;
        
        /**
         * Transforms a position from the internal coordinate system to the coordinate system of this projection.
         * @param pos The position in the internal coordiante system.
         * @return The transformed position in the coordinate system of this projection.
         */
        virtual MapPos fromInternal(const MapPos& pos) const;
        /**
         * Transforms a position from the coordinate system of this projection to the internal coordinate system.
         * @param pos The position in the coordinate system of this projection.
         * @return The transformed position in the internal coordinate system.
         */
        virtual MapPos toInternal(const MapPos& pos) const;
        
        /**
         * Transforms a position from the WGS84 coordinate system to the coordinate system of this projection.
         * @param pos The position in the WGS84 coordinate system.
         * @return The transformed position in the coordinate system of this projection.
         */
        virtual MapPos fromWgs84(const MapPos& pos) const = 0;
        /**
         * Transforms a position from the coordinate system of this projection to the WGS84 coordinate system.
         * @param pos The position in the coordinate system of this projection.
         * @return The transformed position in the WGS84 coordinate system.
         */
        virtual MapPos toWgs84(const MapPos &pos) const = 0;
    
        /**
         * Return name of this projection in Well-Known format. For example, as "EPSG:3857"
         * @return The name of this projection.
         */
        virtual std::string getName() const = 0;
    
    protected:
        Projection(const std::string& className, const MapBounds& bounds);
    
        MapBounds _bounds;
        
        std::string _className; // This is used by swig to generate correct proxy object

    private:
        static const int EARTH_RADIUS = 6371000;
    };
    
}

#endif
