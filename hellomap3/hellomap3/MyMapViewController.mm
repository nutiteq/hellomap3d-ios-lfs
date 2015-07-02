#import "MyMapViewController.h"

@interface MyMapViewController ()

@end

@implementation MyMapViewController

- (void)loadView
{
    // The initial step: register your license. This must be done before using MapView!
    // You can get your free/commercial license from: http://developer.nutiteq.com
    // The license string used here is intended only for Nutiteq demos and WILL NOT WORK with other apps!
    [NTMapView registerLicense:@"XTUN3Q0ZBd2NtcmFxbUJtT1h4QnlIZ2F2ZXR0Mi9TY2JBaFJoZDNtTjUvSjJLay9aNUdSVjdnMnJwVXduQnc9PQoKcHJvZHVjdHM9c2RrLWlvcy0zLiosc2RrLWFuZHJvaWQtMy4qCnBhY2thZ2VOYW1lPWNvbS5udXRpdGVxLioKYnVuZGxlSWRlbnRpZmllcj1jb20ubnV0aXRlcS4qCndhdGVybWFyaz1ldmFsdWF0aW9uCnVzZXJLZXk9MTVjZDkxMzEwNzJkNmRmNjhiOGE1NGZlZGE1YjA0OTYK"];
    
    [super loadView];
}

- (void)viewDidLoad
{
	[super viewDidLoad];

    // GLKViewController-specific parameters for smoother animations
    [self setResumeOnDidBecomeActive: NO];
    [self setPreferredFramesPerSecond: 60];
    
    // The storyboard has NTMapView connected as a view
    NTMapView* mapView = (NTMapView*) self.view;
	
	// Set the base projection, that will be used for most MapView, MapEventListener and Options methods
	NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
    [[mapView getOptions] setBaseProjection:proj]; // EPSG3857 is actually the default base projection, so this is actually not needed
    
	// General options
	[[mapView getOptions] setRotatable:YES]; // make map rotatable (this is actually the default)
	[[mapView getOptions] setTileThreadPoolSize:2]; // use 2 threads to download tiles
	
  [[mapView getOptions] setZoomRange:[[NTMapRange alloc]initWithMin:11 max:17]];
  NTTileDataSource
    // Set initial location and other parameters, don't animate
    [mapView setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
    [mapView setZoom:14 durationSeconds:0];
    [mapView setRotation:0 durationSeconds:0];
    
	// Create online vector tile layer, use style asset embedded in the project
	NTVectorTileLayer* vectorTileLayer = [[NTNutiteqOnlineVectorTileLayer alloc] initWithStyleAssetName:@"osmbright.zip"];

	// Add vector tile layer
    [[mapView getLayers] add:vectorTileLayer];

	// Load bitmaps for custom markers
	UIImage* markerImage = [UIImage imageNamed:@"marker.png"];
	NTBitmap* markerBitmap = [NTBitmapUtils createBitmapFromUIImage:markerImage];
	
	// Create a marker style, use it for both markers, because they should look the same
	NTMarkerStyleBuilder* markerStyleBuilder = [[NTMarkerStyleBuilder alloc] init];
	[markerStyleBuilder setBitmap:markerBitmap];
	[markerStyleBuilder setSize:30];
	NTMarkerStyle* sharedMarkerStyle = [markerStyleBuilder buildStyle];
	
	// Initialize a local vector data source
    NTLocalVectorDataSource* vectorDataSource = [[NTLocalVectorDataSource alloc] initWithProjection:proj];

	// Create marker, add it to the data source
	NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.426939]]; // Tallinn
	NTMarker* marker = [[NTMarker alloc] initWithPos:pos style:sharedMarkerStyle];
	[vectorDataSource add:marker];

	// Initialize a vector layer with the previous data source
    NTVectorLayer* vectorLayer = [[NTVectorLayer alloc] initWithDataSource:vectorDataSource];

	// Add the previous vector layer to the map
    [[mapView getLayers] add:vectorLayer];
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    // GLKViewController-specific, do on-demand rendering instead of constant redrawing
    // This is VERY IMPORTANT as it stops battery drain when nothing changes on the screen!
    [self setPaused:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
