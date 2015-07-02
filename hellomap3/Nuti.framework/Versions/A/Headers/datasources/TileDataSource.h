/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TILEDATASOURCE_H_
#define _NUTI_TILEDATASOURCE_H_

#include <mutex>
#include <memory>
#include <vector>

#include "core/MapTile.h"
#include "core/TileData.h"

namespace Nuti {
    class Projection;

    /**
     * Abstract base class for tile data sources. It provides default implementation 
     * for listener registration and other common tile data source methods.
     */
    class TileDataSource : public std::enable_shared_from_this<TileDataSource> {
    public:
        /**
         * Interface for monitoring data source change events.
         */
        struct OnChangeListener {
            virtual ~OnChangeListener() { }
    
            /**
             * Listener method that gets called when tiles have changes and need to be updated.
             * If the removeTiles flag is set all caches should be cleared prior to updating.
             * @param removeTiles The remove tiles flag.
             */
            virtual void onTilesChanged(bool removeTiles) = 0;
        };
        
        /**
         * Constructs an abstract TileDataSource object.
         * Note: EPSG3857 projection is used.
         * @param minZoom The minimum zoom level supported by this data source.
         * @param maxZoom The maximum zoom level supported by this data source.
         */
        TileDataSource(int minZoom, int maxZoom);
        
        virtual ~TileDataSource();
        
        /**
         * Returns the minimum zoom level supported by this data source.
         * @return The minimum zoom level supported (inclusive).
         */
        int getMinZoom() const;
        /**
         * Returns the maximum zoom level supported by this data source.
         * @return The maximum zoom level supported (exclusive).
         */
        int getMaxZoom() const;
        /**
         * Returns the projection of this tile source.
         * @return The projection of this tile source.
         */
        const std::shared_ptr<Projection>& getProjection() const;
        
        /**
         * Loads the specified tile.
         * @param tile The tile to load.
         * @return The tile data. If the tile is not available, null may be returned.
         */
        virtual std::shared_ptr<TileData> loadTile(const MapTile& tile) = 0;
    
        /**
         * Notifies listeners that the tiles have changed. Action taken depends on the implementation of the
         * listeners, but generally all cached tiles will be reloaded. If the removeTiles flag is set all caches will be cleared
         * prior to reloading, if it's not set then the reloaded tiles will replace the old tiles in caches as they finish loading.
         * @param removeTiles The remove tiles flag.
         */
        virtual void notifyTilesChanged(bool removeTiles);
    
        /**
         * Registers listener for data source change events.
         * @param listener The listener for change events.
         */
        void registerOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);
    
        /**
         * Unregisters listener from data source change events.
         * @param listener The previously added listener.
         */
        void unregisterOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);
    
    protected:
        int _minZoom;
        int _maxZoom;
        std::shared_ptr<Projection> _projection;
    
    private:
        std::vector<std::shared_ptr<OnChangeListener> > _onChangeListeners;
        mutable std::mutex _onChangeListenersMutex;
    };
    
}

#endif
