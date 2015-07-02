/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_ANIMATIONHANDLER_H_
#define _NUTI_ANIMATIONHANDLER_H_

#include "core/MapPos.h"

#include <memory>
#include <mutex>

namespace Nuti {
    class MapRenderer;
    class ViewState;
    
    class AnimationHandler {
    public:
        AnimationHandler(MapRenderer& mapRenderer);
        virtual ~AnimationHandler();
    
        void calculate(const ViewState& viewState, float deltaSeconds);
    
        void setPanTarget(const MapPos& panTarget, float durationSeconds);
        void stopPan();
        
        void setRotationTarget(float rotationTarget, const MapPos* targetPos, float durationSeconds);
        void stopRotation();
        
        void setTiltTarget(float tiltTarget, float durationSeconds);
        void stopTilt();
        
        void setZoomTarget(float zoomTarget, const MapPos* targetPos, float durationSeconds);
        void stopZoom();
    
    private:
        void calculatePan(const ViewState& viewState, float deltaSeconds);
        void calculateRotation(const ViewState& viewState, float deltaSeconds);
        void calculateTilt(const ViewState& viewState, float deltaSeconds);
        void calculateZoom(const ViewState& viewState, float deltaSeconds);
    
        bool _panStarted;
        float _panDurationSeconds;
        MapPos _panTarget;
    
        bool _rotationStarted;
        float _rotationDurationSeconds;
        float _rotationTarget;
        std::unique_ptr<MapPos> _rotationTargetPos;
    
        bool _tiltStarted;
        float _tiltDurationSeconds;
        float _tiltTarget;
    
        bool _zoomStarted;
        float _zoomDurationSeconds;
        float _zoomTarget;
        std::unique_ptr<MapPos> _zoomTargetPos;
    
        MapRenderer& _mapRenderer;
    
        mutable std::mutex _mutex;
    };
    
}

#endif
