/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TEXTSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_TEXTSYMBOLIZER_H_

#include "TileSymbolizer.h"
#include "ParserUtils.h"
#include "FontSet.h"
#include "Expression.h"
#include "Map.h"

#include <vector>

namespace Nuti { namespace MapnikVT {
	class TextSymbolizer : public TileSymbolizer {
	public:
		TextSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map, const std::shared_ptr<Mapnik::Expression>& textExpression, const std::vector<std::shared_ptr<Mapnik::FontSet>>& fontSets) : TileSymbolizer(logger, map), _textExpression(textExpression), _fontSets(fontSets) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		std::shared_ptr<Mapnik::Expression> getTextExpression() const;
		std::shared_ptr<VT::Font> getFont(const TileSymbolizerContext& symbolizerContext) const;
		VT::TextFormatter::Options getFormatterOptions(const TileSymbolizerContext& symbolizerContext) const;

		const std::shared_ptr<Mapnik::Expression> _textExpression;
		const std::vector<std::shared_ptr<Mapnik::FontSet>> _fontSets;
		std::string _fieldName;
		std::string _textTransform;
		std::string _faceName;
		std::string _fontSetName;
		std::string _placement = "point";
		float _size = 10.0f;
		unsigned int _fill = 0xff000000;
		unsigned int _haloFill = 0xffffffff;
		float _haloRadius = 0.0f;
		float _opacity = 1.0f;
		float _dx = 0.0f;
		float _dy = 0.0f;
		float _minimumDistance = 0.0f;
		bool _allowOverlap = false;
		float _wrapWidth = 0.0f;
		bool _wrapBefore = false;
		float _characterSpacing = 0.0f;
		float _lineSpacing = 0.0f;
		std::string _horizontalAlignment = "auto";
		std::string _verticalAlignment = "auto";
	};
} }

#endif
