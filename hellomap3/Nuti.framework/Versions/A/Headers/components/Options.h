/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_OPTIONS_H_
#define _NUTI_OPTIONS_H_

#include "core/MapBounds.h"
#include "core/MapRange.h"
#include "graphics/Color.h"
#include "projections/Projection.h"

#include <memory>
#include <mutex>
#include <vector>

namespace Nuti {
    class Bitmap;
    class CancelableThreadPool;
    
    namespace ProjectionMode {
        /**
         *  Possible projection modes.
         */
        enum ProjectionMode {
            /**
             * Orthogonal projection mode means that the size of the objects on the screen
             * does not depend on their distance from the camera. This might be useful because it 
             * avoids perspective distortion, but it becomes unusable at small tilt angles. 
             * This is sometimes confused with isometric projection which is a subtype of 
             * orthogonal projection.
             */
            PROJECTION_MODE_ORTHOGONAL,
            /**
             * Perspective projection means that the further away objects get from the camera the smaller
             * they appear on the screen. This projection mode is used in most 3D games and applications.
             */
            PROJECTION_MODE_PERSPECTIVE
        };
    };
    
    namespace PanningMode {
        /**
         *  Possible panning modes for dual touch user input.
         */
        enum PanningMode {
            /**
             * Free panning means that the map panning is unrestricted, user is able to zoom, rotate and 
             * pan the map at the same time without any artificial limits.
             */
            PANNING_MODE_FREE,
            /**
             * Sticky panning means that the map panning is restricted, user is able to freely pan the map,
             * but zooming and rotating gestures can't be performed at the same time. User is still able to 
             * switch between zooming and rotating the map but it takes a bit more effort compared to FREE panning.
             * gesture is performed and
             */
            PANNING_MODE_STICKY,
            /**
             * Final sticky panning means that the map panning is restricted, user is able to freely pan the map,
             * but zooming and rotating gestures can't be performed at the same time. Once the gesture type is 
             * determined the user is stuck with either zooming or rotating. To switch the gesture the user has to lift
             * at least one the two fingers off the screen.
             */
            PANNING_MODE_STICKY_FINAL
        };
    };
    
    /**
     * A class containing various options for rendering and map manipulation.
     */
    class Options {
    public:
        /**
         * Interface for monitoring options change events.
         */
        struct OnChangeListener {
            virtual ~OnChangeListener() { }
            
            /**
             * Listener method that gets called when an option has changed.
             * @param optionName The name of the option that has changed.
             */
            virtual void onOptionChanged(const std::string& optionName) = 0;
        };

        /**
         * Constructs an Options object with all parameters set to defaults.
         * @param envelopeThreadPool The thread pool used for envelope tasks.
         * @param tileThreadPool The thread pool used for tile tasks.
         */
        Options(const std::shared_ptr<CancelableThreadPool>& envelopeThreadPool, const std::shared_ptr<CancelableThreadPool>& tileThreadPool);
        /**
         * Copy constructs an Options object from another Options object.
         * @param options The other Options object.
         */
        Options(const Options& options);
        virtual ~Options();
        
        /**
         * Returns the color of the ambient light.
         * @return The color of the ambient light.
         */
        Color getAmbientLightColor() const;
        /**
         * Sets the parameters for the ambient light. Ambient light affects all lighting enabled models
         * in the scene equally, it has no direction or location.
         * @param color The new color for the ambient light.
         */
        void setAmbientLight(const Color& color);
        
        /**
         * Returns the color of the main light.
         * @return The color of the main light.
         */
        Color getMainLightColor() const;
        /**
         * Returns the direction of the main light.
         * @return The direction of the main light.
         */
        MapVec getMainLightDirection() const;
        /**
         * Sets the parameters for the main light. The main light affects all lighting enabled models
         * in the scene equally from a certain direction. This light can be used to simulate sun or moon light.
         * @param color The new color for the main light.
         * @param direction The new direction vector for the main light. (0,0,-1) means straight down, (-0.707,0,-0.707) means
         *        from east with a 45 degree angle. The direction vector will be normalized.
         */
        void setMainLight(const Color& color, const MapVec& direction);
    
        /**
         * Returns the projection mode.
         * @return The projection mode.
         */
        ProjectionMode::ProjectionMode getProjectionMode() const;
        /**
         * Sets the projection mode. The default is ProjectionMode::PERSPECTIVE.
         * @param projectionMode The new projection mode.
         */
        void setProjectionMode(ProjectionMode::ProjectionMode projectionMode);
    
        /**
         * Returns the click type detection state.
         * @return True if click type detecton is enabled.
         */
        bool isClickTypeDetection() const;
        /**
         * Sets the state of the click type detection flag. If set to true clicks are categorized as normal clicks, double clicks,
         * long clicks and dual clicks. The click type resolving take about 400ms, so for applications that do not 
         * require this functionality, it can be turned off. The default is true.
         * @param enabled The new state of the click type detection flag.
         */
        void setClickTypeDetecton(bool enabled);
    
        /**
         * Returns the tile size used for drawing map tiles.
         * @return The tile size in density-independent pixels (dp).
         */
        int getTileDrawSize() const;
        /**
         * Sets the tile size for drawing map tiles. Different datasources may have different tile sizes, this option
         * can be used to compensate for bigger or smaller tiles than default. The default is 256.
         * @param tileDrawSize The new tile size in density-independent pixels (dp).
         */
        void setTileDrawSize(int tileDrawSize);
    
        /**
         * Returns the dots per inch value.
         * @return The dots per inch value.
         */
        float getDPI() const;
        /**
         * Sets the dots per inch value. This is calculated automatically by the SDK when the MapView is created using 
         * the device screen parameters. The purpose of this value is to compensate for very high or low resolution devices,
         * so that the map remains readable.
         * @param dpi The new dots per inch value.
         */
        void setDPI(float dpi);
    
        /**
         * Returns the draw distance value.
         * @return The draw distance value.
         */
        float getDrawDistance() const;
        /**
         * Sets a new draw distance value. The higher the draw distance the more tiles can be seen, if the map is tilted.
         * Changing the draw distance will cause the horizon to move, which means that the if the sky bitmap is used,
         * the horizon may not match up anymore. Increasing this value will decrease performance and increase network traffic, 
         * if online map is used. The default is 16.
         * @param drawDistance The new draw distance value.
         */
        void setDrawDistance(float drawDistance);
    
        /**
         * Returns the vertial field of view angle.
         * @return The vertical field of view angle in degrees.
         */
        int getFieldOfViewY() const;
        /**
         * Sets the vertial field of view angle. Larger values increase the viewable area, at the cost of performance and
         * additional perspective distortion. The default is 70.
         * @param fovY The new vertical field of view angle in degrees.
         */
        void setFieldOfViewY(int fovY);
    
        /**
         * Returns the panning mode.
         * @return The panning mode.
         */
        PanningMode::PanningMode getPanningMode() const;
        /**
         * Sets the panning mode. The default is PanningMode::FREE.
         * @param panningMode The new panning mode.
         */
        void setPanningMode(PanningMode::PanningMode panningMode);
    
        /**
         * Returns the state of seamless horizontal panning flag.
         * @return True if seamless horizontal panning is enabled.
         */
        bool isSeamlessPanning() const;
        /**
         * Sets the state of seamless horizontal panning flag. If set to true, the user can scroll seamlessly from
         * the left side of the map to the right, and the other way around. The default is true.
         * @param enabled The new state of seamless horizontal panning flag.
         */
        void setSeamlessPanning(bool enabled);
    
        /**
         * Returns the number of threads used by the envelope task pool.
         * @return The envelope task thread pool size.
         */
        int getEnvelopeThreadPoolSize() const;
        /**
         * Sets the number of threads used by the envelope task pool. More threads means more envelope tasks 
         * are executed in parallel. This might speed up the data query, but may cause performance drops. Default is 1.
         * @param poolSize The new envelope task thread pool size.
         */
        void setEnvelopeThreadPoolSize(int poolSize);
    
        /**
         * Returns the number of threads used by the tile task pool.
         * @return The tile task thread pool size.
         */
        int getTileThreadPoolSize() const;
        /**
         * Sets the number of threads used by the tile task pool. More threads means more tile tasks
         * are executed in parallel. This might speed up the data query, but may cause performance drops. Default is 1.
         * @param poolSize The new tile task thread pool size.
         */
        void setTileThreadPoolSize(int poolSize);
    
        /**
        * Returns the background bitmap. May be null.
        * @return The background bitmap.
        */
        std::shared_ptr<Bitmap> getBackgroundBitmap() const;
        /**
         * Sets the background bitmap. The purpose of the background bitmap is to fill out the empty space when there's
         * no map data visible. The bitmap will get scaled and repeated to cover the hole visible area. If a null pointer is passed, 
         * the background won't be drawn.
         * The width and height of the bitmap must be power of two (for example: 256 * 256 or 128 * 512). 
         * It's also preferred if the bitmap was square (width == height), but this is not a requirement. 
         * The default is "default_background.png".
         * @param backgroundBitmap The new background bitmap.
         */
        void setBackgroundBitmap(const std::shared_ptr<Bitmap>& backgroundBitmap);
    
        /**
         * Returns the sky bitmap. May be null.
         * @return The sky bitmap.
         */
        std::shared_ptr<Bitmap> getSkyBitmap() const;
        /**
         * Sets the sky bitmap. The purpose of the sky bitmap is to fill out the empty space visible at low tilt angles.
         * The bitmap is folded horizontally into 4 equal parts making up the north, east, south and west sides of the sky.
         * The horizon of the sky should be vertically centered, for references look at the default sky bitmap bundled with the SDK.
         * If a null pointer is passed, the sky won't be drawn.
         * The width and height of the bitmap must be power of two (for example: 256 * 256 or 128 * 512). In the most common
         * use case the width of the bitmap is 4 times the height (width == 4 * height), but this is not a requirement.  
         * The default is "default_sky.png".
         * @param skyBitmap The new sky bitmap.
         */
        void setSkyBitmap(const std::shared_ptr<Bitmap>& skyBitmap);
        
        /**
         * Returns the horizontal alignment of the watermark.
         * @return The horizontal alignment of the watermark.
         */
        float getWatermarkAlignmentX() const;
        /**
         * Returns the vertical alignment of the watermark.
         * @return The vertical alignment of the watermark.
         */
        float getWatermarkAlignmentY() const;
        /**
         * Sets the position of the watermark relative to the screen. Values will be clamped to [-1, 1] range.
         * @param alignmentX The new horizontal alignment for the watermark. -1 means the left side,
         * 0 the center and 1 the right side. The default is 1.
         * @param alignmentY The new vertical alignment for the watermark. -1 means the bottom,
         * 0 the center and 1 the top. The default is -1.
         */
        void setWatermarkAlignment(float alignmentX, float alignmentY);
    
        /**
         * Returns the watermark relative scale.
         * @return The watermark relative scale. The default is 1.
         */
        float getWatermarkScale() const;
        /**
         * Set the watermark relative scale. By default, watermark size is independant of the actual watermark bitmap size.
         * This method can be used to change this.
         * @param scale The new relative scale value.
         */
        void setWatermarkScale(float scale);
        
        /**
         * Returns the watermark bitmap. May be null.
         * @return The watermark bitmap.
         */
        std::shared_ptr<Bitmap> getWatermarkBitmap() const;
        /**
         * Sets the watermark bitmap. This is only available with enterprise licenses. The watermark will be displayed
         * on top of the map view in a user chosen corner. If null is passed no watermark will be displayed.
         * @param watermarkBitmap The new watermark bitmap.
         */
        void setWatermarkBitmap(const std::shared_ptr<Bitmap>& watermarkBitmap);
        
        /**
         * Returns the horizontal padding of the watermark.
         * @return The horizontal padding of the watermark in dp.
         */
        float getWatermarkPaddingX() const;
        /**
         * Returns the vertical padding of the watermark.
         * @return The vertical padding of the watermark in dp.
         */
        float getWatermarkPaddingY() const;
        /**
         * Sets the padding between the watermark and the edge of the screen.
         * @param paddingX The new horizontal padding for the watermark in dp. The default is 4.
         * @param paddingY The new vertical padding for the watermark in dp. The default is 4.
         */
        void setWatermarkPadding(float paddingX, float paddingY);
        
        /**
         * Returns the state of the user input flag.
         * @return True if user input is allowed.
         */
        bool isUserInput() const;
        /**
         * Sets the state of the user input flag. If set to false the user won't be able to pan the map using touch controls,
         * programmatic map panning using MapView methods is still possible. The default is false.
         * @param enabled The new state of the user input flag.
         */
        void setUserInput(bool enabled);
    
        /**
         * Returns the state of the kinetic panning flag.
         * @return True if kinetic panning is enabled.
         */
        bool isKineticPan();
        /**
         * Sets the state of the kinetic panning flag. Kinetic panning allows the map to pan automatically using
         * the inertia of the last swipe, after the user has finished interacting with the touch screen.
         * Default is true.
         * @param enabled The new state of the kinetic panning flag.
         */
        void setKineticPan(bool enabled);
    
        /**
         * Returns the state of the kinetic rotation flag.
         * @return True if kinetic rotation is enabled.
         */
        bool isKineticRotation();
        /**
         * Sets the state of the kinetic rotation flag. Kinetic rotation allows the map to rotate automatically using
         * the inertia of the last swipe, after the user has finished interacting with the touch screen.
         * Default is true.
         * @param enabled The new state of the kinetic rotation flag.
         */
        void setKineticRotation(bool enabled);
        
        /**
         * Returns the state of kinetic zoom flag.
         * @return True if kinetic zooming is enabled.
         */
        bool isKineticZoom();
        /**
         * Sets the state of the kinetic zooming flag. Kinetic zooming allows the map to zoom automatically using
         * the inertia of the last swipe, after the user has finished interacting with the touch screen.
         * Default is true.
         * @param enabled The new state of the kinetic zooming flag.
         */
        void setKineticZoom(bool enabled);
    
        /**
         * Returns the state of the map rotatability flag.
         * @return True if map rotating is enabled.
         */
        bool isRotatable() const;
        /**
         * Sets the state of the map rotatability flag. If set to false the map can't be rotated by any means. The default is true.
         * @param enabled The new state of the map rotatability flag.
         */
        void setRotatable(bool enabled);
    
        /**
         * Returns the tilt range constraint.
         * @return The tilt range constraint in degrees.
         */
        const MapRange& getTiltRange() const;
        /**
         * Sets the tilt range constraint. This will limit the tilt angle of the camera to the specified range.
         * The current tilt angle will remain unaffected, until the next time the tilt angle changes.
         * The minimum tilt angle is 30 degrees and the maximum is 90 degrees. Values that are out of range will be clamped.
         * The default value is MapRange(30, 90).
         * @param tiltRange The new tilt range constraint in degrees.
         */
        void setTiltRange(const MapRange& tiltRange);
    
        /**
         * Returns the zoom range constraint.
         * @return The zoom range constraint.
         */
        const MapRange& getZoomRange() const;
        /**
         * Sets the zoom range constraint. This will limit the zoom level of the camera to the specified range.
         * The current zoom level will remain unaffected, until the next time the zoom level changes.
         * The minimum zoom value is 0 and the maximum is 24. Values that are out of range will be clamped.
         * The default value is MapRange(0, 24).
         * @param zoomRange The new zoom range constraint.
         */
        void setZoomRange(const MapRange& zoomRange);
        
        /**
         * Returns the map panning bounds constraints. Map bounds minimum and maximum points are in the internal coordinate system.
         * @return The map bounds constraints.
         */
        const MapBounds& getInternalPanBounds() const;
        /**
         * Returns the map panning bounds constraints. Map bounds minimum and maximum points are in the base
         * projection's coordinate system.
         * @return The map bounds constraints.
         */
        MapBounds getPanBounds() const;
        /**
         * Sets the map panning bounds constraints. This will limit camera movement to the specified bounds.
         * The current camera position will remain unaffected, until the next time camera position changes.
         * Map bounds minimum and maximum points are expected to be in the base projection's coordinate system.
         * If the bounds are larger than the world size, they will be clamped to world bounds. The default value covers the 
         * whole world.
         * @param panBounds The new map bounds constraints.
         */
        void setPanBounds(const MapBounds& panBounds);
    
        /**
         * Returns the base projection.
         * @return The base projection.
         */
        std::shared_ptr<Projection> getBaseProjection() const;
        /**
         * Sets the base projection. All MapView, MapEventListener and Options methods use the coordinate system of this projection.
         * For example, if base projection is set to EPSG3857 then MapView::getFocusPos returns the coordinates in the EPSG3857 coordinate system,
         * The same applies to setter methods like MapView::setFocusPos which expect the input coordinates to be in the base projection's coordinate system.
         * The default is EPSG3857.
         * @param baseProjection The new base projection.
         */
        void setBaseProjection(const std::shared_ptr<Projection>& baseProjection);
		
        Options& operator = (const Options& options);

        /**
         * Registers listener for options change events.
         * @param listener The listener for change events.
         */
        void registerOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);
        
        /**
         * Unregisters listener from options change events.
         * @param listener The previously added listener.
         */
        void unregisterOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);

	private:
        static std::shared_ptr<Bitmap> GetDefaultBackgroundBitmap();
        static std::shared_ptr<Bitmap> GetDefaultSkyBitmap();
        static std::shared_ptr<Bitmap> GetDefaultWatermarkBitmap();
    
        static std::shared_ptr<Bitmap> _DefaultBackgroundBitmap;
        static std::shared_ptr<Bitmap> _DefaultSkyBitmap;
        static std::shared_ptr<Bitmap> _DefaultWatermarkBitmap;
		
        static std::mutex _Mutex;
        
        void notifyOptionChanged(const std::string& optionName);
        
        Color _ambientLightColor;
        Color _mainLightColor;
        MapVec _mainLightDir;
    
        ProjectionMode::ProjectionMode _projectionMode;
    
        bool _clickTypeDetection;
    
        int _tileDrawSize;
    
        float _dpi;
    
        float _drawDistance;
    
        int _fovY;
    
        PanningMode::PanningMode _panningMode;
    
        bool _seamlessPanning;
    
        int _zoomLevelBias;
    
        std::shared_ptr<Bitmap> _backgroundBitmap;
        std::shared_ptr<Bitmap> _skyBitmap;
        
        float _watermarkAlignmentX;
        float _watermarkAlignmentY;
        std::shared_ptr<Bitmap> _watermarkBitmap;
        float _watermarkPaddingX;
        float _watermarkPaddingY;
        float _watermarkScale;
        
        bool _userInput;
    
        bool _kineticPan;
        bool _kineticRotation;
        bool _kineticZoom;
    
        bool _rotatable;
        MapRange _tiltRange;
        MapRange _zoomRange;
        MapBounds _panBounds;
    
        std::shared_ptr<Projection> _baseProjection;
    
        std::shared_ptr<CancelableThreadPool> _envelopeThreadPool;
        std::shared_ptr<CancelableThreadPool> _tileThreadPool;
    
        mutable std::mutex _mutex;

        std::vector<std::shared_ptr<OnChangeListener> > _onChangeListeners;
        mutable std::mutex _onChangeListenersMutex;
    };
	
}

#endif
