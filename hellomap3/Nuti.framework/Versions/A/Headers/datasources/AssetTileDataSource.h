/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_ASSETTILEDATASOURCE_H_
#define _NUTI_ASSETTILEDATASOURCE_H_

#include "TileDataSource.h"

#include <string>

namespace Nuti {
    
    /**
     * A tile data source where each map tile is a seperate image file bundled with the application.
     * The requests are generated using a template scheme, where tags in the basePath string are replaced with actual values.
     * The following tags are supported: zoom, x, y, xflipped, yflipped, quadkey.
     *
     * For example, if basePath = "t{zoom}_{x}_{y}.png" and the requested tile has zoom == 2,
     * x == 1 and y == 3, then the tile will be loaded from the following path: "t2_1_2.png".
     */
    class AssetTileDataSource : public TileDataSource {
    public:
        /**
         * Constructs an AssetTileDataSource object.
         * @param minZoom The minimum zoom level supported by this data source.
         * @param maxZoom The maximum zoom level supported by this data source.
         * @param basePath The base path containing tags (for example, "t{zoom}_{x}_{y}.png").
         */
        AssetTileDataSource(int minZoom, int maxZoom, const std::string& basePath);
        virtual ~AssetTileDataSource();
    
        virtual std::shared_ptr<TileData> loadTile(const MapTile& tile);
    
    protected:
        virtual std::string buildAssetPath(const MapTile& tile);
    
        std::string _basePath;
    };
    
}

#endif
