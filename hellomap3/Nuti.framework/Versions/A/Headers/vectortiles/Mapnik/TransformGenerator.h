/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_TRANSFORMGENERATOR_H_
#define _NUTI_MAPNIK_TRANSFORMGENERATOR_H_

#include "Transform.h"

#include <memory>
#include <functional>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/karma_alternative.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

namespace Nuti {
	namespace Mapnik {
		namespace TransformGeneratorImpl {
			namespace phx = boost::phoenix;
			namespace karma = boost::spirit::karma;
			namespace ascii = boost::spirit::ascii;

			template <typename OutputIterator>
			struct Grammar : karma::grammar<OutputIterator, std::shared_ptr<Transform>(), ascii::space_type> {
				Grammar() : Grammar::base_type(transform) {
					using karma::_pass;
					using karma::_val;
					using karma::_1;
					using karma::_2;
					using karma::_3;
					using karma::_4;
					using karma::_5;
					using karma::_6;

					number %= karma::float_;

					transform %=
						  matrix
						| translate
						| rotate
						| scale
						| skewx
						| skewy
						;

					matrix =
						(karma::lit("matrix") << '(' << number << ',' << number << ',' << number << ',' << number << ',' << number << ',' << number << ')') [_pass = phx::bind(&getMatrixTransform, _val, _1, _2, _3, _4, _5, _6)]
						;

					translate =
						(karma::lit("translate") << '(' << number << ',' << number << ')') [_pass = phx::bind(&getTranslateTransform, _val, _1, _2)]
						;

					rotate =
						(karma::lit("rotate") << '(' << number << ',' << number << ',' << number << ')') [_pass = phx::bind(&getRotateTransform, _val, _1, _2, _3)]
						;

					scale =
						(karma::lit("scale") << '(' << number << ',' << number << ')')[_pass = phx::bind(&getScaleTransform, _val, _1, _2)]
						;

					skewx =
						(karma::lit("skewx") << '(' << number << ')') [_pass = phx::bind(&getSkewTransform<SkewXTransform>, _val, _1)]
						;

					skewy =
						(karma::lit("skewy") << '(' << number << ')') [_pass = phx::bind(&getSkewTransform<SkewYTransform>, _val, _1)]
						;
				}

				karma::rule<OutputIterator, float()> number;
				karma::rule<OutputIterator, std::shared_ptr<Transform>(), ascii::space_type> transform, matrix, translate, rotate, scale, skewx, skewy;

			private:
				static bool getMatrixTransform(const std::shared_ptr<Transform>& transform, float& a, float& b, float& c, float& d, float& e, float& f) {
					if (auto matrixTransform = std::dynamic_pointer_cast<MatrixTransform>(transform)) {
						cglib::mat3x3<float> m = matrixTransform->getMatrix();
						a = m(0, 0);
						b = m(1, 0);
						c = m(0, 1);
						d = m(1, 1);
						e = m(0, 2);
						f = m(1, 2);
						return true;
					}
					return false;
				}

				static bool getTranslateTransform(const std::shared_ptr<Transform>& transform, float& x, float& y) {
					if (auto translateTransform = std::dynamic_pointer_cast<TranslateTransform>(transform)) {
						x = translateTransform->getPos()(0);
						y = translateTransform->getPos()(1);
						return true;
					}
					return false;
				}

				static bool getRotateTransform(const std::shared_ptr<Transform>& transform, float& x, float& y, float& angle) {
					if (auto rotateTransform = std::dynamic_pointer_cast<RotateTransform>(transform)) {
						x = rotateTransform->getPos()(0);
						y = rotateTransform->getPos()(1);
						angle = rotateTransform->getAngle();
						return true;
					}
					return false;
				}

				static bool getScaleTransform(const std::shared_ptr<Transform>& transform, float& sx, float& sy) {
					if (auto scaleTransform = std::dynamic_pointer_cast<ScaleTransform>(transform)) {
						sx = scaleTransform->getScale()(0);
						sy = scaleTransform->getScale()(1);
						return true;
					}
					return false;
				}

				template <typename SkewTransform>
				static bool getSkewTransform(const std::shared_ptr<Transform>& transform, float& angle) {
					if (auto skewTransform = std::dynamic_pointer_cast<SkewTransform>(transform)) {
						angle = skewTransform->getAngle();
						return true;
					}
					return false;
				}
			};
		}

		template <typename Iterator> using TransformGenerator = TransformGeneratorImpl::Grammar<Iterator>;
	}
}

#endif