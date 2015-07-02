/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_PLATFORMUTILS_H_
#define _NUTI_PLATFORMUTILS_H_

#include <string>
#include <mutex>

namespace Nuti {
    
    namespace PlatformType {
        enum PlatformType {
            PLATFORM_TYPE_ANDROID,
            PLATFORM_TYPE_IOS,
            PLATFORM_TYPE_MAC_OS,
            PLATFORM_TYPE_WINDOWS,
            PLATFORM_TYPE_WINDOWS_PHONE,
            PLATFORM_TYPE_XAMARIN_IOS,
            PLATFORM_TYPE_XAMARIN_ANDROID
        };
    };
    
    class PlatformUtils {
    public:
        static PlatformType::PlatformType GetPlatformType();
        
        static std::string GetDeviceId();
        
        static std::string GetAppIdentifier();

        static std::string GetAppDeviceId();
        
        static bool ExcludeFolderFromBackup(const std::string& folder);
        
    private:
        PlatformUtils();
    };
    
}

#endif
