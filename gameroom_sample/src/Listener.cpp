#include "Listener.h"

void GameListener::onLoginAccessTokenMsg(fbgAccessTokenHandle accessTokenHandle) {
    auto isValid = fbg_AccessToken_IsValid(accessTokenHandle);
    if (!isValid) {
        // user not logged in
        return;
    }

    auto userid = fbg_AccessToken_GetUserID(accessTokenHandle);

    char token_string[512];
    auto size = fbg_AccessToken_GetTokenString(accessTokenHandle, token_string, 512);
    auto expiration_timestamp = fbg_AccessToken_GetExpirationTimestamp(accessTokenHandle);

    fbgLoginScope permissions[512];
    auto permissionCount = fbg_AccessToken_GetPermissions(accessTokenHandle, permissions, 512);

    ::printf(
        "User ID: %lld\nAccess Token: %s\nExpiration Timestamp: %lld, Permission Count: %zu\nPermissions: ",
        (long long)userid,
        token_string,
        (long long)expiration_timestamp,
        permissionCount
    );

    for (int i = 0; i < permissionCount; i++) {
        ::printf("%s", fbgLoginScope_ToString(permissions[i]));
    }
    ::printf("\n");
}

void GameListener::onFeedShareMsg(fbgFeedShareHandle feedShareHandle) {
    auto postId = fbg_FeedShare_GetPostID(feedShareHandle);
    ::printf(
        "Feed Share Post ID: %ld\n",
        (long)postId
    );
}

void GameListener::onPurchaseIAPMsg(fbgPurchaseHandle payHandle) {
    size_t size;
    char paymentId[512];
    size = fbg_Purchase_GetPaymentID(payHandle, paymentId, 512);

    auto amount = fbg_Purchase_GetAmount(payHandle);

    char currency[512];
    size = fbg_Purchase_GetCurrency(payHandle, currency, 512);

    auto purchaseTime = fbg_Purchase_GetPurchaseTime(payHandle);

    char productId[512];
    size = fbg_Purchase_GetProductId(payHandle, productId, 512);

    char purchaseToken[512];
    size = fbg_Purchase_GetPurchaseToken(payHandle, purchaseToken, 512);

    auto quantity = fbg_Purchase_GetQuantity(payHandle);

    char requestId[512];
    size = fbg_Purchase_GetRequestId(payHandle, requestId, 512);

    char status[512];
    size = fbg_Purchase_GetStatus(payHandle, status, 512);

    char signedRequest[512];
    size = fbg_Purchase_GetSignedRequest(payHandle, signedRequest, 512);

    auto errorCode = fbg_Purchase_GetErrorCode(payHandle);

    char errorMessage[512];
    size = fbg_Purchase_GetErrorMessage(payHandle, errorMessage, 512);

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
    auto hasLicense = fbg_HasLicense_GetHasLicense(hasLicenseHandle);
    ::printf(
        "Has License: %llu",
        hasLicense
    );
}