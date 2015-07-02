/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_MARKERSSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_MARKERSSYMBOLIZER_H_

#include "TileSymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class MarkersSymbolizer : public TileSymbolizer {
	public:
		MarkersSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		static std::shared_ptr<VT::Bitmap> makeEllipseBitmap(int width, int height);
		static std::shared_ptr<VT::Bitmap> makeArrowBitmap(int width, int height);

		const int DEFAULT_CIRCLE_SIZE = 10;
		const int DEFAULT_ARROW_WIDTH = 28, DEFAULT_ARROW_HEIGHT = 14;

		std::string _file;
		std::string _placement = "point";
		std::string _markerType;
		unsigned int _fill = 0xff0000ff;
		float _opacity = 1.0f;
		float _width = -1;
		float _height = -1;
		float _spacing = 100;
		bool _allowOverlap = false;
		bool _ignorePlacement = false;
		cglib::mat3x3<float> _transform = cglib::mat3x3<float>::identity();
	};
} }

#endif
