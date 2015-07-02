/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_POINTSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_POINTSYMBOLIZER_H_

#include "TileSymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class PointSymbolizer : public TileSymbolizer {
	public:
		PointSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		static std::shared_ptr<VT::Bitmap> createRectangleBitmap(int size);

		const int RECTANGLE_SIZE = 4;

		std::string _file;
		unsigned int _fill = 0xff000000;
		float _opacity = 1.0f;
		float _width = 10;
		float _height = 10;
		bool _allowOverlap = false;
		bool _ignorePlacement = false;
		cglib::mat3x3<float> _transform = cglib::mat3x3<float>::identity();
	};
} }

#endif
