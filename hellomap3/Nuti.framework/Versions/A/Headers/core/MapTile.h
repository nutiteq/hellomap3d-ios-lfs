/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPTILE_H_
#define _NUTI_MAPTILE_H_

#include <string>

namespace Nuti {

    /**
     * An immutable map tile, used by tile layers for representing small pieces of map at different zoom levels and coordinates.
     */
    class MapTile {
    public:
        MapTile(int x, int y, int zoom, int frameNr);
        virtual ~MapTile() {};
    
        /**
         * Checks for equality between this and another map tile.
         * @param tile The other map tile.
         * @return True if equal.
         */
        bool operator ==(const MapTile& tile) const;
        /**
         * Checks for inequality between this and another map tile.
         * @param tile The other map tile.
         * @return True if not equal.
         */
        bool operator !=(const MapTile& tile) const;
    
        /**
         * Returns the x coordinate of this map tile.
         * @return The x coordinate of this map tile.
         */
        int getX() const;
        /**
         * Returns the y coordinate of this map tile.
         * @return The y coordinate of this map tile.
         */
        int getY() const;
        /**
         * Returns the zoom level of this map tile.
         * @return The zoom level of this map tile.
         */
        int getZoom() const;
        /**
         * Returns the time of this map tile.
         * @return The time of this map tile.
         */
        int getFrameNr() const;
    
        /**
         * Returns the internal tile id of this map tile.
         * @return The internal tile id of this map tile.
         */
        long long getTileId() const;
    
		/**
		 * Returns the hash value of this object.
		 * @return The hash value of this object.
		 */
		int hash() const;

		/**
         * Creates a string representation of this map tile, useful for logging.
         * @return The string representation of this map tile.
         */
        std::string toString() const;
        
    protected:
        int _x;
        int _y;
        int _zoom;
        int _frameNr;
    
        long long _id;
    };
    
}

#endif
