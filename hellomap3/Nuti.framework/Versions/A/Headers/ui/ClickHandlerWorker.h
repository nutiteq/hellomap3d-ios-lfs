/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CLICKHANDLERTASK_H_
#define _NUTI_CLICKHANDLERTASK_H_

#include "components/ThreadWorker.h"
#include "core/ScreenPos.h"

#include <chrono>
#include <condition_variable>
#include <thread>

namespace Nuti {
    class Options;
    class TouchHandler;
    
    class ClickHandlerWorker : public ThreadWorker {
    public:
        ClickHandlerWorker(const std::shared_ptr<Options>& options);
        virtual ~ClickHandlerWorker();
        
        void setComponents(const std::weak_ptr<TouchHandler>& touchHandler, const std::shared_ptr<ClickHandlerWorker>& worker);
    
        bool isRunning() const;
    
        void init();
        void stop();
    
        void pointer1Down(const ScreenPos& screenPos);
        void pointer1Moved(const ScreenPos& screenPos);
        void pointer1Up();
    
        void pointer2Down(const ScreenPos& screenPos);
        void pointer2Moved(const ScreenPos& screenPos);
        void pointer2Up();
    
        void cancel();
    
        void operator()();
        
    private:
        enum ClickMode { NO_CLICK, LONG_CLICK, DOUBLE_CLICK, DUAL_CLICK};
        
        static const float LONG_CLICK_MIN_DURATION_S;
        static const float DUAL_CLICK_BEGIN_DURATION_S;
        static const float DUAL_CLICK_END_DURATION_S;
        static const float DOUBLE_CLICK_MAX_DURATION_S;
        
        static const float DOUBLE_CLICK_TOLERANCE_INCHES;
        static const float MOVING_TOLERANCE_INCHES;
        
        void run();
        
        void afterLongClick();
        void afterDoubleClick();
        void afterDualClick();
    
        bool _running;
    
        ClickMode _clickMode;
    
        bool _clickTypeDetection;
        std::chrono::time_point<std::chrono::system_clock> _startTime;
    
        int _pointersDown;
    
        ScreenPos _pointer1Down;
        ScreenPos _pointer1Moved;
        float _pointer1MovedSum;
        ScreenPos _pointer2Down;
        ScreenPos _pointer2Moved;
        float _pointer2MovedSum;
    
        bool _chosen;
        bool _canceled;
    
        std::shared_ptr<Options> _options;
        std::weak_ptr<TouchHandler> _touchHandler;
        std::shared_ptr<ClickHandlerWorker> _worker;
    
        bool _stop;
        std::condition_variable _condition;
        mutable std::mutex _mutex;
    };
    
}

#endif
