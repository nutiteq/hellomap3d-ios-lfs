/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_LINESTYLE_H_
#define _NUTI_LINESTYLE_H_

#include "styles/Style.h"

#include <memory>

namespace Nuti {
    
    namespace LineEndType {
        /**
         * Possible styles in which line end points are drawn.
         */
        enum LineEndType {
            /**
             * No line end points are drawn, line end with a straight line.
             */
            LINE_END_TYPE_STRAIGHT,
            /**
             * Line end points are drawn as half circles.
             */
            LINE_END_TYPE_ROUND};
    };
    
    namespace LineJointType {
        /**
         * Possible styles in which line segments are connected with each other.
         */
        enum LineJointType {
            /**
             * Line segments are not connected with each other. The fastest and ugliest.
             */
            LINE_JOINT_TYPE_NONE,
            /**
             * Line segments are connected with each other using straight line connectors. Fast
             * but results in an unnatural line.
             */
            LINE_JOINT_TYPE_STRAIGHT,
            /**
             * Line segments are connected with each other using circle sectors resulting in 
             * round corners. Slowest and prettiest.
             */
            LINE_JOINT_TYPE_ROUND};
    };
    
    class Bitmap;
    
    /**
     * A style for lines. Contains attributes for configuring how the line is drawn on the screen.
     */
    class LineStyle: public Style {
    public:
        /**
         * Constructs a LineStyle object from various parameters. Instantiating the object directly is
         * not recommended, LineStyleBuilder should be used instead.
         * @param color The color for the line.
         * @param bitmap The bitmap for the line.
         * @param clickWidth The width of the line used for click detection.
         * @param lineEndType The line's end point type.
         * @param lineJointType The joint type for the line.
         * @param stretchFactor The color for the line.
         * @param width The width for the line.
         */
        LineStyle(const Color& color, const std::shared_ptr<Bitmap>& bitmap, float clickWidth,
                LineEndType::LineEndType lineEndType, LineJointType::LineJointType lineJointType,
                float stretchFactor, float width);
        virtual ~LineStyle();
    
        /**
         * Returns the bitmap of the line.
         * @return The bitmap of the line.
         */
        std::shared_ptr<Bitmap> getBitmap() const;
        
        /**
         * Returns the width of the line used for click detection.
         * @return The width of the line used for click detection.
         */
        float getClickWidth() const;
    
        /**
         * Returns the end point type of the line.
         * @return The end point type of the line.
         */
        LineEndType::LineEndType getLineEndType() const;
    
        /**
         * Returns the joint type of the line.
         * @return The joint type of the line.
         */
        LineJointType::LineJointType getLineJointType() const;
    
        /**
         * Returns the stretching factor of the line.
         * @return The stretching factor of the line.
         */
        float getStretchFactor() const;
    
        /**
         * Returns the width of the line.
         * @return The width of the line.
         */
        float getWidth() const;
    
    protected:
        std::shared_ptr<Bitmap> _bitmap;
        
        float _clickWidth;
    
        LineEndType::LineEndType _lineEndType;
    
        LineJointType::LineJointType _lineJointType;
    
        float _stretchFactor;
    
        float _width;
    
    };
    
}

#endif
