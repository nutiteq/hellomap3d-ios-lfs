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

/**
 * Possible image formats.
 */
typedef NS_ENUM(NSInteger, NTColorFormat) {
/**
 * Options for identifiny unsupported image formats.
 */
  NT_COLOR_FORMAT_UNSUPPORTED = 0,
/**
 * An image format that describes images with a single color channel.
 */
  NT_COLOR_FORMAT_GRAYSCALE = 0x1909,
/**
 * An image format that describes images with two channels, one for color and the other<br>
 * for alpha.
 */
  NT_COLOR_FORMAT_GRAYSCALE_ALPHA = 0x190A,
/**
 * An image format that describes images with three channels, one for each color: red, green and blue.
 */
  NT_COLOR_FORMAT_RGB = 0x1907,
/**
 * An image format that describes images with four channels, one for each color: red, green and blue<br>
 * and one for alpha.
 */
  NT_COLOR_FORMAT_RGBA = 0x1908,
/**
 * An image format that describes images with four channels, one for each color: blue, green and red<br>
 * and one for alpha. This color format will be converted to RGBA.
 */
  NT_COLOR_FORMAT_BGRA = 1,
/**
 * An image format that describes images with four channels, one for each color: red, green, and blue<br>
 * and one for alpha. Each color is only four bits. This color format will be converted to RGBA.
 */
  NT_COLOR_FORMAT_RGBA_4444 = 2,
/**
 * An image format that describes images with three channels, one for each color: red, green, and blue.<br>
 * Red and blue colors are each packed into 5 bits, green into 6 bits. This color format will be converted to RGB.
 */
  NT_COLOR_FORMAT_RGB_565 = 3
};


#import "NTUnsignedCharVector.h"

/**
 * A class that provides the functionality to store, compress, uncompress and resize basic image formats.<br>
 * Currently supported formats are png and jpeg. Upon loading compressed images will be converted to<br>
 * alpha premultiplied uncompressed bitmaps of various image formats.
 */
__attribute__ ((visibility("default"))) @interface NTBitmap : NSObject
{
  void *swigCPtr;
  BOOL swigCMemOwn;
}
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**  
 * Checks if this object is equal to the specified object.
 * @return True when objects are equal, false otherwise.
 */
-(BOOL)isEqual:(id)object;

/**
 * Returns the hash value of this object.
 * @return The hash value of this object.
 */
-(NSUInteger)hash;

/**
 * Constructs a bitmap by loading a compressed image bundled with the application. If the power of two conversion flag<br>
 * is set, additional padding will be added to the image to make it's dimensions power of two. This can be useful when creating<br>
 * OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.<br>
 * @param assetPath The path to the image to be loaded.<br>
 * @param pow2Padding The power of two conversion flag.
 */
-(id)initWithAssetPath: (NSString*)assetPath pow2Padding: (BOOL)pow2Padding;
/**
 * Constructs a bitmap by decoding a vector of compressed image bytes. If the power of two conversion flag<br>
 * is set, additional padding will be added to the image to make it's dimensions power of two. This can be useful when creating<br>
 * OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.<br>
 * @param compressedData A vector of compressed image bytes.<br>
 * @param pow2Padding The power of two conversion flag.
 */
-(id)initWithCompressedData: (NTUnsignedCharVector*)compressedData pow2Padding: (BOOL)pow2Padding;
/**
 * Constructs a bitmap from an already decoded vector of bytes. The bitmap data is expected to be alpha premultiplied.<br>
 * If the power of two conversion flag is set, additional padding will be added to the image to make it's dimensions power of two.<br>
 * This can be useful when creating OpenGL textures from the Bitmap, because some GPUs perform badly with non power of two textures.<br>
 * @param uncompressedData A vector of decoded, premultiplied bitmap bytes.<br>
 * @param width The width of the bitmap.<br>
 * @param height The height of the bitmap.<br>
 * @param colorFormat The color format of the bitmap.<br>
 * @param bytesPerRow The total number of bytes per row. Some bitmaps have additional padding at the end of each row. If the value is negative, then bitmap is assumed to be vertically flipped. In this case absolute value of the bytesPerRow value is used.<br>
 * @param pow2Padding The power of two conversion flag.
 */
-(id)initWithUncompressedData: (NTUnsignedCharVector*)uncompressedData width: (unsigned int)width height: (unsigned int)height colorFormat: (enum NTColorFormat)colorFormat bytesPerRow: (int)bytesPerRow pow2Padding: (BOOL)pow2Padding;
/**
 * Returns the width of the bitmap.<br>
 * @return The width of the bitmap.
 */
-(unsigned int)getWidth;
/**
 * Returns the height of the bitmap.<br>
 * @return The height of the bitmap.
 */
-(unsigned int)getHeight;
/**
 * Returns the unpadded width of this bitmap. If power of two padding was added when constructing this bitmap, the original unpadded<br>
 * bitmap's width will be returned. If no padding was added, this method is equivalent to the getWidth() method.<br>
 * @return The width of the bitmap without power of two padding.
 */
-(unsigned int)getOrigWidth;
/**
 * Returns the unpadded height of this bitmap. If power of two padding was added when constructing this bitmap, the original unpadded<br>
 * bitmap's height will be returned. If no padding was added, this method is equivalent to the getHeight() method.<br>
 * @return The height of the bitmap without power of two padding.
 */
-(unsigned int)getOrigHeight;
/**
 * Returns the color format of this bitmap.<br>
 * @return The color format of this bitmap.
 */
-(enum NTColorFormat)getColorFormat;
/**
 * Returns the bytes per pixel parameter of this bitmap. Valid values are 1, 2, 3 and 4.<br>
 * @return The bytes per pixel parameter of this bitmap.
 */
-(unsigned int)getBytesPerPixel;
/**
 * Compresses this bitmap to a png.<br>
 * @return A byte vector of the png's data.
 */
-(NTUnsignedCharVector*)compressToPng;
/**
 * Compresses this bitmap to a internal format.<br>
 * This operation is intended for serialization of the data only, no actual compression is performed.<br>
 * @return A byte vector of the serialized data.
 */
-(NTUnsignedCharVector*)compressToInternal;
/**
 * Returns resized version of the bitmap. The power of two padding added during the construction of this bitmap<br>
 * will be removed prior to resizing. If the power of two conversion flag is set, new padding will be added to the image <br>
 * after resizing to make it's dimensions power of two.<br>
 * @param width The new width of this bitmap.<br>
 * @param height The new height of this bitmap.<br>
 * @param pow2Padding The power of two conversion flag.<br>
 * @return The resized bitmap instance or null in case of error (wrong dimensions).
 */
-(NTBitmap*)getResizedBitmap: (unsigned int)width height: (unsigned int)height pow2Padding: (BOOL)pow2Padding;
/**
 * Returns sub-bitmap with specified offsets and dimensions.<br>
 * @param xOffset X coordinate offset in the bitmap.<br>
 * @param yOffset Y coordinate offset in the bitmap.<br>
 * @param width Width of the sub-bitmap.<br>
 * @param height Height of the sub-bitmap.<br>
 * @param pow2Padding The power of two conversion flag.<br>
 * @return Sub-bitmap instance or null in case of error (wrong dimensions).
 */
-(NTBitmap*)getSubBitmap: (int)xOffset yOffset: (int)yOffset width: (int)width height: (int)height pow2Padding: (BOOL)pow2Padding;
/**
 * Returns copy of the bitmap converted to RGBA format.<br>
 * @param pow2Padding The power of two conversion flag.<br>
 * @return The bitmap with identical dimensions but converted to RGBA format.
 */
-(NTBitmap*)getRGBABitmap: (BOOL)pow2Padding;
/**
 * Returns copy of the bitmap with padding removed.<br>
 * @return The bitmap with original dimensions.
 */
-(NTBitmap*)getUnpaddedBitmap;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

