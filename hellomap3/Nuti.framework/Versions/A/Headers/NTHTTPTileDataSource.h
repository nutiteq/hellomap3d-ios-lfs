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


#import "NTMapTile.h"
#import "NTTileDataSource.h"
#import "NTTileData.h"
#import "NTStringMap.h"

/**
 * A tile data source that loads tiles using a HTTP connection.<br>
 * The requests are generated using a template scheme, where tags in the baseURL string are replaced with actual values.<br>
 * The following tags are supported: zoom, x, y, xflipped, yflipped, quadkey.<br>
 * <br>
 * For example, if baseURL = "http://tile.openstreetmap.org/{zoom}/{x}/{y}.png" and the requested tile has zoom = 2,<br>
 * x = 1 and y = 3, then the tile will be loaded from the following URL: "http://tile.openstreetmap.org/2/1/3.png".
 */
__attribute__ ((visibility("default"))) @interface NTHTTPTileDataSource : NTTileDataSource
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
/**
 * Constructs a HTTPTileDataSource object.<br>
 * @param minZoom The minimum zoom level supported by this data source.<br>
 * @param maxZoom The maximum zoom level supported by this data source.<br>
 * @param baseURL The base URL containing tags (for example, "http://tile.openstreetmap.org/{zoom}/{x}/{y}.png").
 */
-(id)initWithMinZoom: (int)minZoom maxZoom: (int)maxZoom baseURL: (NSString*)baseURL;
/**
 * Returns the current set of HTTP headers used. Initially this set is empty and can be changed with setHTTPHeaders.<br>
 * @return The current set of custom HTTP headers.
 */
-(NTStringMap*)getHTTPHeaders;
/**
 * Sets HTTP headers for all requests.<br>
 * @param headers A map of HTTP headers that will be used in subsequent requests.
 */
-(void)setHTTPHeaders: (NTStringMap*)headers;
-(NTTileData*)loadTile: (NTMapTile*)mapTile;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif
