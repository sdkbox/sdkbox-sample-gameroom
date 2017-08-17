#ifndef __GAMEROOM_WRAPPER_H__
#define __GAMEROOM_WRAPPER_H__

#include "PluginGameroom.h"

#include <Windows.h>
#include <process.h>

namespace sdkbox {
    // don't use singleton here, because CreateThread() function don't support 
    // "std::bind()" to bind a 'this' parameter.
    class GameroomWrapper {
    public:
        GameroomWrapper() = delete;
        ~GameroomWrapper() = delete;

        GameroomWrapper(const GameroomWrapper&) = delete;
        GameroomWrapper(GameroomWrapper&&) = delete;
        GameroomWrapper& operator=(const GameroomWrapper&) = delete;
        GameroomWrapper& operator=(GameroomWrapper&&) = delete;

    public:
        static int init();
        static int destroy();

        static int setListener(GameroomListener*);
        static GameroomListener* removeListener();
        static GameroomListener* listener();

	public:
		static std::string loginWithScopes(uint32_t scopeCount, const std::vector<std::string>& loginScopes);

    private:
        static int createPluginThread();
        static DWORD WINAPI pluginThreadFunc(LPVOID arg);

		static size_t extractLoginScopes(const std::vector<std::string>& loginScopes, LoginScope* scopes);

    private:
        static HANDLE thHandle_;
        static bool isRunning_;
        static GameroomListener* listener_;
    };
}
#endif