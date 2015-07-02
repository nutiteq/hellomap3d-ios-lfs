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


#import "NTMapBounds.h"
#import "NTGeometry.h"
#import "NTStringMap.h"

/**
 * A base class for all vector elements (points, lines, texts, models, etc).
 */
__attribute__ ((visibility("default"))) @interface NTVectorElement : NSObject
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


+(NTVectorElement*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Returns the actual class name of this vector element. This is used<br>
 * for dynamically creating Java and ObjC proxy classes, because Swig can't automatically<br>
 * generate child proxy classes from a base class pointer.<br>
 * @return The class name of this vector element.
 */
-(NSString*)getClassName;
/**
 * Returns the bounds of this vector element.<br>
 * @return The bounds of this vector element.
 */
-(NTMapBounds*)getBounds;
/**
 * Returns the geometry object that defines the location of this vector element.<br>
 * @return The geometry object of this vector element.
 */
-(NTGeometry*)getGeometry;
/**
 * Returns the internal id of this vector element.<br>
 * @return The internal id of this vector element.
 */
-(long long)getId;
/**
 * Sets the internal id for this vector element. The id is used for internal caching, and<br>
 * should not be changed by the user. User id can added to meta data as a key-value pair.<br>
 * @param id The new internal id for this vector element.
 */
-(void)setId: (long long)arg1;
/**
 * Returns a modifiable meta data map. Users may add their data as key-value pairs.<br>
 * @return The modifiable meta data map of this vector element.
 */
-(NTStringMap*)getMetaData;
/**
 * Sets a new meta data map for the vector element. Old meta data values will be lost.<br>
 * @param metaData The new meta data map for this vector element.
 */
-(void)setMetaData: (NTStringMap*)metaData;
/**
 * Returns a meta data element corresponding to the key. If no value is found an empty string is returned.<br>
 * @return The value corresponding to the key from the meta data map. May be null.
 */
-(NSString*)getMetaDataElement: (NSString*)key;
/**
 * Adds a new key-value pair to the meta data map. If the key already exists in the map,<br>
 * it's value will be replaced by the new value.<br>
 * @param key The new key.<br>
 * @param element The new value.
 */
-(void)setMetaDataElement: (NSString*)key element: (NSString*)element;
/**
 * Returns the state of the visibility flag of this vector element.<br>
 * @return True if this vector element is visible.
 */
-(BOOL)isVisible;
/**
 * Sets the state of the visibility flag for this vector element. If set to false the element will not be<br>
 * drawn.<br>
 * @param visible The new state of the visibility flag for the vector element.
 */
-(void)setVisible: (BOOL)visible;
/**
 * Notifies this vector element's datasource about the change in this element.<br>
 * The data source may then notify the layer to update the view.
 */
-(void)notifyElementChanged;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

