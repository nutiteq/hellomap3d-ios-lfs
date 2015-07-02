/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TILEGEOMETRY_H_
#define _NUTI_VT_TILEGEOMETRY_H_

#include "Bitmap.h"
#include "StrokeSet.h"
#include "VertexArray.h"

#include <memory>
#include <array>
#include <vector>

#include <boost/optional.hpp>

#include <cglib/mat.h>

namespace Nuti { namespace VT {
	class TileGeometry {
	public:
		enum class Type {
			NONE, LINE, POLYGON, POLYGON3D
		};

		struct StyleParameters {
			enum { MAX_PARAMETERS = 16 };
			int parameterCount;
			std::array<unsigned int, MAX_PARAMETERS> colorTable;
			std::array<float, MAX_PARAMETERS> lineWidthTable;
			std::shared_ptr<const BitmapPattern> pattern;
			boost::optional<cglib::mat3x3<float>> transform;

			StyleParameters() : parameterCount(0), colorTable(), lineWidthTable(), pattern(), transform() { }
		};

		struct GeometryLayoutParameters {
			int vertexSize;
			int vertexOffset;
			int attribsOffset;
			int texCoordOffset;
			int binormalOffset;
			int heightOffset;
			float vertexScale;
			float texCoordScale;
			float binormalScale;

			GeometryLayoutParameters() : vertexSize(0), vertexOffset(-1), attribsOffset(-1), texCoordOffset(-1), binormalOffset(-1), heightOffset(-1), vertexScale(0), texCoordScale(0), binormalScale(0) { }
		};

		TileGeometry(Type type, float tileSize, const StyleParameters& styleParameters, const GeometryLayoutParameters& geometryLayoutParameters, unsigned int indicesCount, VertexArray<unsigned char>&& vertexGeometry, VertexArray<unsigned short>&& indices) : _type(type), _tileSize(tileSize), _styleParameters(styleParameters), _geometryLayoutParameters(geometryLayoutParameters), _indicesCount(indicesCount), _vertexGeometry(std::move(vertexGeometry)), _indices(std::move(indices)) { }

		Type getType() const { return _type; }
		float getTileSize() const { return _tileSize; }
		const StyleParameters& getStyleParameters() const { return _styleParameters; }
		const GeometryLayoutParameters& getGeometryLayoutParameters() const { return _geometryLayoutParameters; }
		unsigned int getIndicesCount() const { return _indicesCount; }

		const VertexArray<unsigned char>& getVertexGeometry() const { return _vertexGeometry; }
		const VertexArray<unsigned short>& getIndices() const { return _indices; }

		void releaseVertexArrays() {
			_vertexGeometry.clear();
			_indices.clear();
		}

		std::size_t getResidentSize() const {
			return _vertexGeometry.size() * sizeof(unsigned char) + _indices.size() * sizeof(unsigned short);
		}

	private:
		Type _type;
		float _tileSize;
		StyleParameters _styleParameters;
		GeometryLayoutParameters _geometryLayoutParameters;
		unsigned int _indicesCount;

		VertexArray<unsigned char> _vertexGeometry;
		VertexArray<unsigned short> _indices;
	};
} }

#endif
