/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.6
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#import <Foundation/Foundation.h>


#ifdef __cplusplus
extern "C" {
#endif


#import "NTBitmap.h"
#import "NTColor.h"
#import "NTBillboardStyle.h"

/**
 * A style for markers. Contains attributes for configuring how the marker is drawn on the screen.
 */
__attribute__ ((visibility("default"))) @interface NTMarkerStyle : NTBillboardStyle
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
/**
 * Constructs a MarkerStyle object from various parameters. Instantiating the object directly is<br>
 * not recommended, MarkerStyleBuilder should be used instead.<br>
 * @param color The color for the marker.<br>
 * @param attachAnchorPointX The horizontal attaching anchor point for the marker.<br>
 * @param attachAnchorPointY The vertical attaching anchor point for the marker.<br>
 * @param causesOverlap The causes overlap flag for the marker.<br>
 * @param hideIfOverlapped The hide if overlapped flag for the marker.<br>
 * @param horizontalOffset The horizontal offset for the marker.<br>
 * @param verticalOffset The vertical offset for the marker.<br>
 * @param placementPriority The placement priority for the marker.<br>
 * @param scaleWithDPI The scale with DPI flag for the label.<br>
 * @param anchorPointX The horizontal anchor point for the marker.<br>
 * @param anchorPointY The vertical anchor point for the marker.<br>
 * @param bitmap The bitmap for the marker.<br>
 * @param orientationMode The orientation mode for the marker.<br>
 * @param scalingMode The scaling mode for the marker.<br>
 * @param size The size for the marker.
 */
-(id)initWithColor: (NTColor*)color attachAnchorPointX: (float)attachAnchorPointX attachAnchorPointY: (float)attachAnchorPointY causesOverlap: (BOOL)causesOverlap hideIfOverlapped: (BOOL)hideIfOverlapped horizontalOffset: (float)horizontalOffset verticalOffset: (float)verticalOffset placementPriority: (int)placementPriority scaleWithDPI: (BOOL)scaleWithDPI anchorPointX: (float)anchorPointX anchorPointY: (float)anchorPointY bitmap: (NTBitmap*)bitmap orientationMode: (enum NTBillboardOrientation)orientationMode scalingMode: (enum NTBillboardScaling)scalingMode size: (float)size;
/**
 * Returns the horizontal anchor point of the marker.<br>
 * @return The horizontal anchor point of the marker.
 */
-(float)getAnchorPointX;
/**
 * Returns the vertical anchor point of the marker.<br>
 * @return The vertical anchor point of the marker.
 */
-(float)getAnchorPointY;
/**
 * Returns the bitmap of the marker.<br>
 * @return The bitmap of the marker.
 */
-(NTBitmap*)getBitmap;
/**
 * Returns the orientation mode of the marker.<br>
 * @return The orientation mode of the marker.
 */
-(enum NTBillboardOrientation)getOrientationMode;
/**
 * Returns the scaling mode of the marker.<br>
 * @return The scaling mode of the marker.
 */
-(enum NTBillboardScaling)getScalingMode;
/**
 * Returns the size of the marker.<br>
 * @return The size of the marker, units depend on the scaling mode.
 */
-(float)getSize;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

