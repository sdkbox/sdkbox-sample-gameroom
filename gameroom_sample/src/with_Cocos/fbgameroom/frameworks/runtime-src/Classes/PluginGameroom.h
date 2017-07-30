#pragma once
#include "PluginGameroomTypes.h"
#include "fbg/FBG_Platform.h"

#include <cstdio>

// windows header
#include <windows.h>
#include <process.h>

namespace sdkbox {


    class  GameroomListener {
        friend class PluginGameroom;
    public:
        GameroomListener() = default;
        virtual ~GameroomListener() {}

        GameroomListener(const GameroomListener&) = delete;
        GameroomListener(GameroomListener&&) = delete;

        GameroomListener& operator=(GameroomListener&&) = delete;
        GameroomListener& operator=(const GameroomListener&) = delete;

    public:

        virtual void onLoginAccessTokenMsg(AccessTokenHandle obj) = 0;
        virtual void onFeedShareMsg(FeedShareHandle obj) = 0;
        virtual void onPurchaseIAPMsg(PurchaseHandle obj) = 0;
        virtual void onPurchaseTrialware(HasLicenseHandle obj) = 0;
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

    public:
        // methods from Facebook Gameroom SDK.

        // Login, Access Token 
        static bool accessTokenIsValid(AccessTokenHandle obj);
        static FacebookID accessTokenGetUserID(AccessTokenHandle obj);
        static size_t accessTokenGetTokenString(AccessTokenHandle obj, char* buffer, size_t bufferLen);
        static uint64_t accessTokenGetExpirationTimestamp(AccessTokenHandle obj);
        static size_t accessTokenGetPermissions(AccessTokenHandle obj, LoginScope* buffer, size_t bufferLen);
        static const char* loginScopeToString(LoginScope loginScope);

        static bool isLoggedIn();
        static GameroomReq login();
        static GameroomReq loginWithScopes(uint32_t scopeCount, LoginScope* loginScopes);

        // Feed Share
        static FacebookID feedShareGetPostID(FeedShareHandle obj);

        static GameroomReq feedShare(
            const char* toId,
            const char* link,
            const char* linkName,
            const char* linkCaption,
            const char* linkDescription,
            const char* pictureLink,
            const char* mediaSource
        );

        // Purchase
        static size_t purchaseGetPaymentID(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static uint32_t purchaseGetAmount(PurchaseHandle obj);
        static size_t purchaseGetCurrency(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static uint64_t purchaseGetPurchaseTime(PurchaseHandle obj);
        static size_t purchaseGetProductID(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static size_t purchaseGetPurchaseToken(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static uint32_t purchaseGetQuantity(PurchaseHandle obj);
        static size_t purchaseGetRequestID(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static size_t purchaseGetStatus(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static size_t purchaseGetSignedRequest(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static uint64_t purchaseGetErrorCode(PurchaseHandle obj);
        static size_t purchaseGetErrorMessage(PurchaseHandle obj, char* buffer, size_t bufferLen);
        static FacebookID purchaseGetLicense(HasLicenseHandle obj);

        static GameroomReq purchaseIAP(
            const char* product,
            uint32_t quantity,
            uint32_t quantityMin,
            uint32_t quantityMax,
            const char* requestId,
            const char* pricePointId,
            const char* testCurrency
        );
        static GameroomReq purchaseIAPWithProductURL(
            const char* product,
            uint32_t quantity,
            uint32_t quantityMin,
            uint32_t quantityMax,
            const char* requestId,
            const char* pricePointId,
            const char* testCurrency
        );
        static GameroomReq payPremium();
        static GameroomReq hasLicense();


    private:
        static int createPluginThread();

        static DWORD WINAPI pluginThreadFunc(LPVOID arg);

    private:
        static HANDLE thHandle_;
        static bool isRunning_;
        static GameroomListener* listener_;
    };
}