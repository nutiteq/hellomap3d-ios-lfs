/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPRENDERER_H_
#define _NUTI_MAPRENDERER_H_

#include "graphics/ShaderManager.h"
#include "graphics/ViewState.h"
#include "renderers/BackgroundRenderer.h"
#include "renderers/components/AnimationHandler.h"
#include "renderers/components/BillboardSorter.h"
#include "renderers/components/KineticEventHandler.h"
#include "renderers/WatermarkRenderer.h"
#include "renderers/workers/BillboardPlacementWorker.h"
#include "renderers/workers/CullWorker.h"
#include "utils/LicenseUtils.h"
#include "utils/LRUTextureCache.h"

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace Nuti {
    class CameraPanEvent;
    class CameraRotationEvent;
    class CameraTiltEvent;
    class CameraZoomEvent;
    class Bitmap;
    class Layer;
    class Layers;
    class MapPos;
    class ScreenPos;
    class ScreenBounds;
    class MapVec;
    class MapEventListener;
    class MapRenderListener;
    class RedrawRequestListener;
    class Options;
    class VectorElementClickInfo;
    class ThreadWorker;
    class TouchHandler;
    
    class MapRenderer : public std::enable_shared_from_this<MapRenderer> {
    public:
        MapRenderer(const std::shared_ptr<Layers>& layers,
                    const std::shared_ptr<Options>& options,
                    const LicenseType::LicenseType& licenseType);
        virtual ~MapRenderer();

		void init();
        void deinit();
        
        std::vector<std::shared_ptr<Billboard> > getBillboards() const;
    
        MapPos getCameraPos() const;
        MapPos getFocusPos() const;
        MapVec getUpVec() const;
        float getRotation() const;
        float getTilt() const;
        float getZoom() const;
    
        ViewState getViewState() const;
    
        AnimationHandler& getAnimationHandler();
        KineticEventHandler& getKineticEventHandler();
        
        std::shared_ptr<MapEventListener> getMapEventListener() const;
        void setMapEventListener(const std::shared_ptr<MapEventListener>& mapEventListener);
    
        std::shared_ptr<RedrawRequestListener> getRedrawRequestListener() const;
        void setRedrawRequestListener(const std::shared_ptr<RedrawRequestListener>& listener);
        
        void requestRedraw() const;
    
        void captureRendering(const std::shared_ptr<MapRenderListener>& listener, bool waitWhileUpdating);
        
        void calculateCameraEvent(CameraPanEvent& cameraEvent, float durationSeconds, bool updateKinetic);
        void calculateCameraEvent(CameraRotationEvent& cameraEvent, float durationSeconds, bool updateKinetic);
        void calculateCameraEvent(CameraTiltEvent& cameraEvent, float durationSeconds, bool updateKinetic);
        void calculateCameraEvent(CameraZoomEvent& cameraEvent, float durationSeconds, bool updateKinetic);
    
        void moveToFitPoints(const MapPos& center, const std::vector<MapPos>& points, const ScreenBounds& screenBounds,
                             bool integerZoom, bool resetTilt, bool resetRotation, float durationSeconds);
        
        MapPos screenToWorld(const ScreenPos& screenPos, float offsetPercent) const;
        ScreenPos worldToScreen(const MapPos& worldPos) const;
    
        void onSurfaceCreated();
        void onSurfaceChanged(int width, int height);
        void onDrawFrame();
        void onSurfaceDestroyed();
    
        void calculateRayIntersectedElements(const MapPos& targetPos, std::vector<VectorElementClickInfo>& results);
    
        void billboardsChanged();
        void layerChanged(const std::shared_ptr<Layer>& layer, bool delay);
        void viewChanged(bool delay);
    
        void addGlThreadCallback(const std::shared_ptr<ThreadWorker>& glCallback);
        
    private:
		class OptionsListener : public Options::OnChangeListener {
		public:
			OptionsListener(const std::shared_ptr<MapRenderer>& mapRenderer);
			
			virtual void onOptionChanged(const std::string& optionName);
			
		private:
			std::weak_ptr<MapRenderer> _mapRenderer;
		};

		friend TouchHandler;

		static bool DistanceComparator(const VectorElementClickInfo& element1, const VectorElementClickInfo& element2);
    
        void setUpGlState() const;
    
        void drawLayers(float deltaSeconds, const ViewState& viewState);
        
        void handleGlThreadCallbacks();
        void handleRenderCaptureCallbacks();
    
        static const int BILLBOARD_PLACEMENT_TASK_DELAY = 200;
        
        std::chrono::time_point<std::chrono::system_clock> _lastFrameTime;
    
        ViewState _viewState;
    
        ShaderManager _shaderManager;
        LRUTextureCache<std::shared_ptr<Bitmap> > _styleCache;
    
        std::shared_ptr<CullWorker> _cullWorker;
        std::thread _cullThread;
		
		std::shared_ptr<OptionsListener> _optionsListener;
		
        BackgroundRenderer _backgroundRenderer;
        WatermarkRenderer _watermarkRenderer;
        
        BillboardSorter _billboardSorter;
        std::vector<std::shared_ptr<Billboard> > _billboardsBuffer;
    
        bool _billboardsChanged;
        std::shared_ptr<BillboardPlacementWorker> _billboardPlacementWorker;
        std::thread _billboardPlacementThread;
    
        AnimationHandler _animationHandler;
        KineticEventHandler _kineticEventHandler;
        
        std::shared_ptr<MapEventListener> _mapEventListener;
        mutable std::recursive_mutex _mapEventListenerMutex;

        mutable std::atomic<bool> _redrawPending;
        std::shared_ptr<RedrawRequestListener> _redrawRequestListener;
        mutable std::recursive_mutex _redrawRequestListenerMutex;

        std::vector<std::pair<std::shared_ptr<MapRenderListener>, bool> > _mapRenderListeners;
        mutable std::recursive_mutex _mapRenderListenersMutex;

        bool _surfaceChanged;
    
        std::shared_ptr<Layers> _layers;
        std::shared_ptr<Options> _options;
        std::vector<std::shared_ptr<ThreadWorker> > _glThreadCallbacks;
    
        mutable std::recursive_mutex _mutex;
    };
    
}

#endif
