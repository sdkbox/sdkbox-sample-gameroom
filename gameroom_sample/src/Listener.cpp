#include "Listener.h"

void GameListener::onLoginAccessTokenMsg(fbgAccessTokenHandle accessTokenHandle) {
    auto isValid = sdkbox::PluginGameroom::accessTokenIsValid(accessTokenHandle);
    if (!isValid) {
        // user not logged in
        return;
    }
    auto userid = sdkbox::PluginGameroom::accessTokenGetUserID(accessTokenHandle);

    char token_string[512];
    auto size = sdkbox::PluginGameroom::accessTokenGetTokenString(accessTokenHandle, token_string, 512);
    auto expiration_timestamp = sdkbox::PluginGameroom::accessTokenGetExpirationTimestamp(accessTokenHandle);

    fbgLoginScope permissions[512];
    auto permissionCount = sdkbox::PluginGameroom::accessTokenGetPermissions(accessTokenHandle, permissions, 512);

    ::printf(
        "User ID: %lld\nAccess Token: %s\nExpiration Timestamp: %lld, Permission Count: %zu\nPermissions: ",
        (long long)userid,
        token_string,
        (long long)expiration_timestamp,
        permissionCount
    );

    for (int i = 0; i < permissionCount; i++) {
        ::printf("%s", sdkbox::PluginGameroom::loginScopeToString(permissions[i]));
    }
    ::printf("\n");
}

void GameListener::onFeedShareMsg(fbgFeedShareHandle feedShareHandle) {
    auto postId = sdkbox::PluginGameroom::feedShareGetPostID(feedShareHandle);
    ::printf(
        "Feed Share Post ID: %ld\n",
        (long)postId
    );
}

void GameListener::onPurchaseIAPMsg(fbgPurchaseHandle payHandle) {
    size_t size;
    char paymentId[512];
    size = sdkbox::PluginGameroom::purchaseGetPaymentID(payHandle, paymentId, 512);

    auto amount = sdkbox::PluginGameroom::purchaseGetAmount(payHandle);

    char currency[512];
    size = sdkbox::PluginGameroom::purchaseGetCurrency(payHandle, currency, 512);

    auto purchaseTime = sdkbox::PluginGameroom::purchaseGetPurchaseTime(payHandle);

    char productId[512];
    size = sdkbox::PluginGameroom::purchaseGetProductID(payHandle, productId, 512);

    char purchaseToken[512];
    size = sdkbox::PluginGameroom::purchaseGetPurchaseToken(payHandle, purchaseToken, 512);

    auto quantity = sdkbox::PluginGameroom::purchaseGetQuantity(payHandle);

    char requestId[512];
    size = sdkbox::PluginGameroom::purchaseGetRequestID(payHandle, requestId, 512);

    char status[512];
    size = sdkbox::PluginGameroom::purchaseGetStatus(payHandle, status, 512);

    char signedRequest[512];
    size = sdkbox::PluginGameroom::purchaseGetSignedRequest(payHandle, signedRequest, 512);

    auto errorCode = sdkbox::PluginGameroom::purchaseGetErrorCode(payHandle);

    char errorMessage[512];
    size = sdkbox::PluginGameroom::purchaseGetErrorMessage(payHandle, errorMessage, 512);

    ::printf(
        "Purchase Handle: %s\nAmount: %d\nCurrency: %s\nPurchase Time: %lld\n"
        "Product Id:%s\nPurchase Token: %s\nQuantity: %d\nRequest Id: %s\n"
        "Status: %s\nSignedRequest: %s\nError Code: %lld\nErrorMessage: %s\n",
        paymentId,
        (int)amount,
        currency,
        (long long)purchaseTime,
        productId,
        purchaseToken,
        (int)quantity,
        requestId,
        status,
        signedRequest,
        (long long)errorCode,
        errorMessage
    );
}

void GameListener::onPurchaseTrialware(fbgHasLicenseHandle hasLicenseHandle) {
    auto hasLicense = sdkbox::PluginGameroom::purchaseGetLicense(hasLicenseHandle);
    ::printf(
        "Has License: %llu",
        hasLicense
    );
}