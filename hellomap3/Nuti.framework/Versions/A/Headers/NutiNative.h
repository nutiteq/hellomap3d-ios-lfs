/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTINATIVE_H_
#define _NUTINATIVE_H_

#include "components/Options.h"

#include "core/MapBounds.h"
#include "core/MapEnvelope.h"
#include "core/MapPos.h"
#include "core/ScreenPos.h"
#include "core/ScreenBounds.h"
#include "core/MapRange.h"
#include "core/MapTile.h"
#include "core/MapVec.h"
#include "core/TileData.h"

#include "datasources/AssetTileDataSource.h"
#include "datasources/BitmapOverlayRasterTileDataSource.h"
#include "datasources/HTTPTileDataSource.h"
#include "datasources/MBTilesTileDataSource.h"
#include "datasources/NutiteqOnlineTileDataSource.h"
#include "datasources/PackageManagerTileDataSource.h"
#include "datasources/OnlineNMLModelLODTreeDataSource.h"
#include "datasources/SqliteNMLModelLODTreeDataSource.h"
#include "datasources/PersistentCacheTileDataSource.h"
#include "datasources/LocalVectorDataSource.h"
#include "datasources/OGRVectorDataSource.h"
#include "datasources/GDALRasterTileDataSource.h"

#include "geometry/LineGeometry.h"
#include "geometry/PointGeometry.h"
#include "geometry/PolygonGeometry.h"
#include "geometry/GeometrySimplifier.h"
#include "geometry/DouglasPeuckerGeometrySimplifier.h"

#include "graphics/Frustum.h"
#include "graphics/Bitmap.h"
#include "graphics/Color.h"
#include "graphics/MapTileQuadTreeNode.h"
#include "graphics/ViewState.h"

#include "layers/Layers.h"
#include "layers/NMLModelLODTreeLayer.h"
#include "layers/RasterTileLayer.h"
#include "layers/TileLoadListener.h"
#include "layers/VectorLayer.h"
#include "layers/VectorTileLayer.h"
#include "layers/NutiteqOnlineVectorTileLayer.h"

#include "projections/EPSG3857.h"

#include "packagemanager/PackageInfo.h"
#include "packagemanager/PackageStatus.h"
#include "packagemanager/PackageTileMask.h"
#include "packagemanager/PackageManager.h"
#include "packagemanager/NutiteqPackageManager.h"

#include "renderers/components/CullState.h"

#include "styles/BalloonPopupStyleBuilder.h"
#include "styles/BalloonPopupStyle.h"
#include "styles/LabelStyleBuilder.h"
#include "styles/LabelStyle.h"
#include "styles/LineStyleBuilder.h"
#include "styles/LineStyle.h"
#include "styles/MarkerStyleBuilder.h"
#include "styles/MarkerStyle.h"
#include "styles/PointStyleBuilder.h"
#include "styles/PointStyle.h"
#include "styles/Polygon3DStyleBuilder.h"
#include "styles/Polygon3DStyle.h"
#include "styles/PolygonStyleBuilder.h"
#include "styles/PolygonStyle.h"
#include "styles/PopupStyleBuilder.h"
#include "styles/PopupStyle.h"
#include "styles/TextStyleBuilder.h"
#include "styles/TextStyle.h"
#include "styles/StyleSelector.h"
#include "styles/StyleSelectorBuilder.h"
#include "styles/StyleSelectorRule.h"
#include "styles/StyleSelectorExpression.h"

#include "ui/BaseMapView.h"
#include "ui/MapView.h"
#include "ui/MapViewController.h"
#include "ui/MapClickInfo.h"
#include "ui/MapEventListener.h"
#include "ui/MapRenderListener.h"
#include "ui/VectorElementClickInfo.h"
#include "ui/VectorElementsClickInfo.h"

#include "utils/AssetUtils.h"
#include "utils/BitmapUtils.h"
#include "utils/Const.h"
#include "utils/Log.h"

#include "vectorelements/BalloonPopup.h"
#include "vectorelements/Label.h"
#include "vectorelements/Line.h"
#include "vectorelements/Marker.h"
#include "vectorelements/NMLModel.h"
#include "vectorelements/NMLModelLODTree.h"
#include "vectorelements/Point.h"
#include "vectorelements/Polygon3D.h"
#include "vectorelements/Polygon.h"
#include "vectorelements/Popup.h"
#include "vectorelements/Text.h"

#include "vectortiles/MBVectorTileStyleSet.h"
#include "vectortiles/MBVectorTileDecoder.h"

#endif
