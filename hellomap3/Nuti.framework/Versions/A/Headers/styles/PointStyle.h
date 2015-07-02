/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POINTSTYLE_H_
#define _NUTI_POINTSTYLE_H_

#include "styles/Style.h"

#include <memory>

namespace Nuti {
    class Bitmap;
    
    /**
     * A style for points. Contains attributes for configuring how the point is drawn on the screen.
     */
    class PointStyle: public Style {
    public:
        /**
         * Constructs a PointStyle object from various parameters. Instantiating the object directly is
         * not recommended, PointStyleBuilder should be used instead.
         * @param color The color for the point.
         * @param bitmap The bitmap for the point.
         * @param clickSize The size of the point used for click detection.
         * @param size The size for the point.
         */
        PointStyle(const Color& color, const std::shared_ptr<Bitmap>& bitmap, float clickSize, float size);
        virtual ~PointStyle();
    
        /**
         * Returns the bitmap of the point.
         * @return The bitmap of the point.
         */
        std::shared_ptr<Bitmap> getBitmap() const;
        
        /**
         * Returns the size of the point used for click detection.
         * @return The size of the point used for click detection.
         */
        float getClickSize() const;
    
        /**
         * Returns the size of the point.
         * @return The size of the point.
         */
        float getSize() const;
    
    protected:
        std::shared_ptr<Bitmap> _bitmap;
        
        float _clickSize;
    
        float _size;
    };
    
}

#endif
