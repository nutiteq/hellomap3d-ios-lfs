/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TILESYMBOLIZER_H_
#define _NUTI_MAPNIKVT_TILESYMBOLIZER_H_

#include "Symbolizer.h"
#include "Features.h"
#include "Expression.h"
#include "ExpressionContext.h"
#include "ExpressionBinder.h"
#include "ParserUtils.h"
#include "TileLayerBuilder.h"
#include "TileSymbolizerContext.h"
#include "Logger.h"
#include "Map.h"

#include <memory>
#include <mutex>

#include <cglib/mat.h>

namespace Nuti { namespace MapnikVT {
	class TileSymbolizer : public Mapnik::Symbolizer {
	public:
		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) = 0;

	protected:
		TileSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map);

		static VT::LabelOrientation convertLabelPlacement(const std::string& orientation);
		static cglib::mat3x3<float> convertTransform(const Mapnik::Value& val);
		static unsigned int convertColor(const Mapnik::Value& val);
		static unsigned int createColor(unsigned int color, float opacity);

		static long long getTextId(long long id, std::size_t hash);
		static long long getBitmapId(long long id, const std::string& file);
		static long long getMultiMarkerId(long long id);

		template <typename V>
		void bind(V* field, const std::shared_ptr<Mapnik::Expression>& expr) {
			_binder.bind(field, expr);
		}

		template <typename V>
		void bind(V* field, const std::shared_ptr<Mapnik::Expression>& expr, V (*convertFn)(const Mapnik::Value& val)) {
			_binder.bind(field, expr, convertFn);
		}

		void updateBindings(const Mapnik::ExpressionContext& exprContext) {
			_binder.evaluate(exprContext);
		}

		mutable std::mutex _mutex; // guards internal state as bindings may update it

		std::shared_ptr<Mapnik::Logger> _logger;

	private:
		Mapnik::ExpressionBinder _binder;
	};
} }

#endif
