#include "PluginGameroom.h"

// no need, but for formalization.
#include "GameroomWrapper.h"  

namespace sdkbox {

	int PluginGameroom::init(const char* appID) {
		auto initializeResult = fbg_PlatformInitializeWindows(appID);
		if (initializeResult != fbgPlatformInitialize_Success) {
			return FAILURE;
		}

		return GameroomWrapper::init();
	}

	int PluginGameroom::destroy() {
		return GameroomWrapper::destroy();
	}

	int PluginGameroom::setListener(GameroomListener *l) {
		return GameroomWrapper::setListener(l);
	}

	GameroomListener * PluginGameroom::removeListener() {
		return GameroomWrapper::removeListener();
	}

	GameroomListener * PluginGameroom::listener() {
		return GameroomWrapper::listener();
	}

	// TODO: Any loggin method in Gameroom SDK?
	void PluginGameroom::log(const char* msg) {
		::printf("%s\n", msg);
	}

	bool PluginGameroom::accessTokenIsValid(AccessTokenHandle obj) {
		return fbg_AccessToken_IsValid(obj);
	}

	FacebookID PluginGameroom::accessTokenGetUserID(AccessTokenHandle obj) {
		return fbg_AccessToken_GetUserID(obj);
	}

	size_t PluginGameroom::accessTokenGetTokenString(AccessTokenHandle obj, char * buffer, size_t bufferLen) {
		return fbg_AccessToken_GetTokenString(obj, buffer, bufferLen);
	}

	uint64_t PluginGameroom::accessTokenGetExpirationTimestamp(AccessTokenHandle obj) {
		return fbg_AccessToken_GetExpirationTimestamp(obj);
	}

	size_t PluginGameroom::accessTokenGetPermissions(AccessTokenHandle obj, LoginScope * buffer, size_t bufferLen) {
		return fbg_AccessToken_GetPermissions(obj, buffer, bufferLen);
	}

	const char * PluginGameroom::loginScopeToString(LoginScope loginScope) {
		return fbgLoginScope_ToString(loginScope);
	}

	bool PluginGameroom::isLoggedIn() {
		return fbg_IsLoggedIn();
	}

	std::string PluginGameroom::login() {
		return std::to_string(fbg_Login());
	}

	std::string PluginGameroom::loginWithScopes(uint32_t scopeCount, const std::vector<std::string>& loginScopes) {
		return GameroomWrapper::loginWithScopes(scopeCount, loginScopes);
	}

	FacebookID PluginGameroom::feedShareGetPostID(FeedShareHandle obj) {
		return fbg_FeedShare_GetPostID(obj);
	}

	std::string PluginGameroom::feedShare(const char * toId, const char * link, const char * linkName, const char * linkCaption, const char * linkDescription, const char * pictureLink, const char * mediaSource) {
		return std::to_string(fbg_FeedShare(toId, link, linkName, linkCaption, linkDescription, pictureLink, mediaSource));
	}

	size_t PluginGameroom::purchaseGetPaymentID(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetPaymentID(obj, buffer, bufferLen);
	}

	uint32_t PluginGameroom::purchaseGetAmount(PurchaseHandle obj) {
		return fbg_Purchase_GetAmount(obj);
	}

	size_t PluginGameroom::purchaseGetCurrency(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetCurrency(obj, buffer, bufferLen);
	}

	uint64_t PluginGameroom::purchaseGetPurchaseTime(PurchaseHandle obj) {
		return fbg_Purchase_GetPurchaseTime(obj);
	}

	size_t PluginGameroom::purchaseGetProductID(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetProductId(obj, buffer, bufferLen);
	}

	size_t PluginGameroom::purchaseGetPurchaseToken(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetPurchaseToken(obj, buffer, bufferLen);
	}

	uint32_t PluginGameroom::purchaseGetQuantity(PurchaseHandle obj) {
		return fbg_Purchase_GetQuantity(obj);
	}

	size_t PluginGameroom::purchaseGetRequestID(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetRequestId(obj, buffer, bufferLen);
	}

	size_t PluginGameroom::purchaseGetStatus(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetStatus(obj, buffer, bufferLen);
	}

	size_t PluginGameroom::purchaseGetSignedRequest(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetSignedRequest(obj, buffer, bufferLen);
	}

	uint64_t PluginGameroom::purchaseGetErrorCode(PurchaseHandle obj) {
		return fbg_Purchase_GetErrorCode(obj);
	}

	size_t PluginGameroom::purchaseGetErrorMessage(PurchaseHandle obj, char * buffer, size_t bufferLen) {
		return fbg_Purchase_GetErrorMessage(obj, buffer, bufferLen);
	}

	FacebookID PluginGameroom::purchaseGetLicense(HasLicenseHandle obj) {
		return fbg_HasLicense_GetHasLicense(obj);
	}

	std::string PluginGameroom::purchaseIAP(const char * product, uint32_t quantity, uint32_t quantityMin, uint32_t quantityMax, const char * requestId, const char * pricePointId, const char * testCurrency) {
		return std::to_string(fbg_PurchaseIAP(product, quantity, quantityMax, quantityMin, requestId, pricePointId, testCurrency));
	}

	std::string PluginGameroom::purchaseIAPWithProductURL(const char * product, uint32_t quantity, uint32_t quantityMin, uint32_t quantityMax, const char * requestId, const char * pricePointId, const char * testCurrency) {
		return std::to_string(fbg_PurchaseIAPWithProductURL(product, quantity, quantityMax, quantityMin, requestId, pricePointId, testCurrency));
	}

	std::string PluginGameroom::payPremium() {
		return std::to_string(fbg_PayPremium());
	}

	std::string PluginGameroom::hasLicense() {
		return std::to_string(fbg_HasLicense());
	}

}

