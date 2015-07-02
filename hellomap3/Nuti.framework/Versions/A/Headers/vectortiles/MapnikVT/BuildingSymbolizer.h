/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_BUILDINGSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_BUILDINGSYMBOLIZER_H_

#include "GeometrySymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class BuildingSymbolizer : public GeometrySymbolizer {
	public:
		BuildingSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : GeometrySymbolizer(logger, map) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		const float HEIGHT_SCALE = static_cast<float>(0.5 / 20037508.34);

		unsigned int _fill = 0xff808080;
		float _fillOpacity = 1.0f;
		float _height = 0.0f;
	};
} }

#endif
