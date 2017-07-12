#pragma once
#include "fbg/FBG_Platform.h"

#include <cstdio>

// windows header
#include <windows.h>
#include <process.h>

namespace sdkbox {
    enum {
        SUCCESS = 0,
        FAILURE = 1,
        THREAD_SUSPEND_INTERVAL = 20
    };

    class  GameroomListener {
    public:
        GameroomListener() = default;
        virtual ~GameroomListener() {}

        GameroomListener(const GameroomListener&) = delete;
        GameroomListener(GameroomListener&&) = delete;

        GameroomListener& operator=(GameroomListener&&) = delete;
        GameroomListener& operator=(const GameroomListener&) = delete;

    public:
        virtual void onLoginAccessTokenMsg(fbgAccessTokenHandle) = 0;
        virtual void onFeedShareMsg(fbgFeedShareHandle) = 0;
        virtual void onPurchaseIAPMsg(fbgPurchaseHandle) = 0;
        virtual void onPurchaseTrialware(fbgHasLicenseHandle) = 0;
    };

    class PluginGameroom {
    public:
        PluginGameroom() = default;
        ~PluginGameroom() = default;

        PluginGameroom(const PluginGameroom&) = delete;
        PluginGameroom(PluginGameroom&&) = delete;

        PluginGameroom& operator=(const PluginGameroom&) = delete;
        PluginGameroom& operator=(PluginGameroom&&) = delete;

    public:
        static int init(const char* appID);

        static int destroy();

        static void setListener(GameroomListener* listener);
        static GameroomListener* listener() { return listener_; }

        static void log(const char* msg);

    private:
        static int createPluginThread();

        static DWORD WINAPI pluginThreadFunc(LPVOID arg);

    private:
        static HANDLE thHandle_;
        static bool isRunning_;
        static GameroomListener* listener_;
    };


}