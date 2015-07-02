/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOMETRYSIMPLIFIER_H_
#define _NUTI_GEOMETRYSIMPLIFIER_H_

#include <memory>
#include <string>

namespace Nuti {
    class Geometry;

    /**
     * Base class for geometry simplifiers.
     */
    class GeometrySimplifier {
    public:
        virtual ~GeometrySimplifier() { }

        /**
         * Returns the actual class name of this geometry. This is used
         * for dynamically creating Java and ObjC proxy classes, because Swig can't automatically
         * generate child proxy classes from a base class pointer.
         * @return The class name of this layer.
         */
        const std::string& getClassName() const { return _className; }

        /**
         * Perform the simplification of the given geometry, given relative scale.
         * @param geometry The geometry to simplify.
         * @param scale Relative scale for simplification, this is proportional to 2^zoom.
         * @return The simplified geometry. If simplification failed, original geometry may be returned. 
         *         Null pointer may be returned if geometry should be discarded.
         */
        virtual std::shared_ptr<Geometry> simplify(const std::shared_ptr<Geometry>& geometry, float scale) const = 0;
        
    protected:
        GeometrySimplifier(const std::string& className) : _className(className) { }
        
    private:
        std::string _className; // This is used by swig to generate correct proxy object
    };
}

#endif
