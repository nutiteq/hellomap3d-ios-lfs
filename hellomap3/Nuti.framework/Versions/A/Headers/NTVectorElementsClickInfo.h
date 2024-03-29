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


#import "NTMapClickInfo.h"
#import "NTVectorElementClickInfoVector.h"

/**
 * A container class that stores information about clicked vector elements.<br>
 * <br>
 * A single click may result in multiple vector elements being returned, all of which are <br>
 * located at the click position. If that's the case, the vector elements will be sorted<br>
 * by their distance to the camera and their draw order. The first VectorElementClickInfo in the<br>
 * vector of VectorElementClickInfos corresponds to the top-most element on the screen.
 */
__attribute__ ((visibility("default"))) @interface NTVectorElementsClickInfo : NSObject
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
 * Returns the click type.<br>
 * @return The type of the click performed.
 */
-(enum NTClickType)getClickType;
/**
 * Returns the sorted list of VectorElementClickInfo objects.<br>
 * @return The list of VectorElementClickInfo objects sorted by their distance to the camera and <br>
 *         their draw order. The first element in the vector is the top-most element on the screen.
 */
-(NTVectorElementClickInfoVector*)getVectorElementClickInfos;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

