#include "PluginGameroomJSHelper.h"
#include "PluginGameroom/PluginGameroom.h"
#include "SDKBoxJSHelper.h"

#include <map>
#include <string>

using namespace sdkbox;

namespace {
    JSContext* s_cx = nullptr;
}

JSOBJECT* FBGAccessTokenHandleToJS(JSContext* cx, const fbgAccessTokenHandle& handle)
{
    JS_INIT_CONTEXT_FOR_UPDATE(cx);

    JSOBJECT* jsobj = JS_NEW_OBJECT(cx);

    auto is_valid_token = sdkbox::PluginGameroom::accessTokenIsValid(handle);
    addProperty(cx, jsobj, "isValidToken", is_valid_token);
    if (!is_valid_token) {
        return jsobj;
    }

    char token_string[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::accessTokenGetTokenString(handle, token_string, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "tokenString", token_string);

    // As xxx_id is usually an unsigned 64bit int,
    // we transform it to std::string. (sic passim)
    auto user_id = sdkbox::PluginGameroom::accessTokenGetUserID(handle);
    addProperty(cx, jsobj, "userID", std::to_string(user_id));

    auto expired_time = sdkbox::PluginGameroom::accessTokenGetExpirationTimestamp(handle);
    addProperty(cx, jsobj, "expiredTime", std::to_string(expired_time));

    fbgLoginScope permissions[FBG_BUFFER_SIZE];
    auto permission_size = sdkbox::PluginGameroom::accessTokenGetPermissions(handle, permissions, FBG_BUFFER_SIZE);

    JSOBJECT *js_permissions = JS_NEW_ARRAY(cx, permission_size);
    for (size_t i = 0; i < permission_size; ++i) {
		JSOBJECT* permission_obj = JS_NEW_OBJECT(cx);
		addProperty(cx, permission_obj, std::to_string(i).c_str(), fbgLoginScope_ToString(permissions[i]));
		JS_ARRAY_SET(cx, js_permissions, i, permission_obj);
    }
    addProperty(cx, jsobj, "permissions", js_permissions);

    return jsobj;
}

JSOBJECT* FBGFeedShareHandleToJS(JSContext* cx, const fbgFeedShareHandle& handle)
{
    JS_INIT_CONTEXT_FOR_UPDATE(cx);

    JSOBJECT* jsobj = JS_NEW_OBJECT(cx);

    auto post_id = sdkbox::PluginGameroom::feedShareGetPostID(handle);
    addProperty(cx, jsobj, "postID", std::to_string(post_id));

    return jsobj;
}

JSOBJECT* FBGHasLicenseHandleToJS(JSContext* cx, const fbgHasLicenseHandle& handle)
{
    JS_INIT_CONTEXT_FOR_UPDATE(cx);

    JSOBJECT* jsobj = JS_NEW_OBJECT(cx);

    auto has_license = sdkbox::PluginGameroom::purchaseGetLicense(handle);
    addProperty(cx, jsobj, "hasLicense", std::to_string(has_license));

    return jsobj;
}

JSOBJECT* FBGPurchaseHandleToJS(JSContext* cx, const fbgPurchaseHandle& handle)
{
    JS_INIT_CONTEXT_FOR_UPDATE(cx);

    JSOBJECT* jsobj = JS_NEW_OBJECT(cx);

    char payment_id[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetPaymentID(handle, payment_id, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "paymentID", payment_id);

    auto amount = sdkbox::PluginGameroom::purchaseGetAmount(handle);
    // uint32_t also larger than int.
    addProperty(cx, jsobj, "amount", std::to_string(amount));

    char currency[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetCurrency(handle, currency, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "currency", currency);

    auto purchase_time = sdkbox::PluginGameroom::purchaseGetPurchaseTime(handle);
    addProperty(cx, jsobj, "purchaseTime", std::to_string(purchase_time));

    char product_id[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetProductID(handle, product_id, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "productID", product_id);

    char purchase_token[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetPurchaseToken(handle, purchase_token, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "purchaseToken", purchase_token);

    auto quantity = sdkbox::PluginGameroom::purchaseGetQuantity(handle);
    addProperty(cx, jsobj, "quantity", std::to_string(quantity)); // uint32_t.

    char request_id[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetRequestID(handle, request_id, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "requestID", request_id);

    char status[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetStatus(handle, status, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "status", status);

    char signed_request[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetSignedRequest(handle, signed_request, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "signedReq", signed_request);

    auto error_code = sdkbox::PluginGameroom::purchaseGetErrorCode(handle); // uint64_t
    addProperty(cx, jsobj, "errorCode", std::to_string(error_code));

    char error_msg[FBG_BUFFER_SIZE];
    sdkbox::PluginGameroom::purchaseGetErrorMessage(handle, error_msg, FBG_BUFFER_SIZE);
    addProperty(cx, jsobj, "errorMsg", error_msg);

    return jsobj;
}

class GameroomListenerJSHelper: public sdkbox::GameroomListener, public sdkbox::JSListenerBase
{
public:

    GameroomListenerJSHelper():sdkbox::JSListenerBase() {
    }

public:

    void onLoginAccessTokenMsg(AccessTokenHandle handle) {
        JS::Value js_args[1];

#if MOZJS_MAJOR_VERSION < 52
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
#endif

        js_args[0] = JS::ObjectValue(*FBGAccessTokenHandleToJS(s_cx, handle));
        invokeDelegate("onLoginAccessTokenMsg", js_args, 1);
    }

    void onFeedShareMsg(FeedShareHandle handle) {
        JS::Value js_args[1];

#if MOZJS_MAJOR_VERSION < 52
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
#endif

        js_args[0] = JS::ObjectValue(*FBGFeedShareHandleToJS(s_cx, handle));
        invokeDelegate("onFeedShareMsg", js_args, 1);
    }

    void onPurchaseIAPMsg(PurchaseHandle handle) {
        JS::Value js_args[1];

#if MOZJS_MAJOR_VERSION < 52
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
#endif

        js_args[0] = JS::ObjectValue(*FBGPurchaseHandleToJS(s_cx, handle));
        invokeDelegate("onPurchaseIAPMsg", js_args, 1);
    }

    void onPurchaseTrialware(HasLicenseHandle handle) {
        JS::Value js_args[1];

#if MOZJS_MAJOR_VERSION < 52
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
#endif

        js_args[0] = JS::ObjectValue(*FBGHasLicenseHandleToJS(s_cx, handle));
        invokeDelegate("onPurchaseTrialware", js_args, 1);
    }

private:

    void invokeDelegate(const std::string& fName, JS::Value dataVal[], int argc) {
        if (!s_cx) {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = fName.c_str();

        JS::RootedObject obj(cx, getJSDelegate());
        JSAutoCompartment ac(cx, obj);

#if MOZJS_MAJOR_VERSION >= 31
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#elif MOZJS_MAJOR_VERSION >= 28
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#else
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JS::NullValue()) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            if (0 == argc) {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::empty(), &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(argc, dataVal), &retval);
            }
#else
            if (0 == argc) {
                JS_CallFunctionName(cx, obj, func_name, 0, nullptr, &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, argc, dataVal, &retval);
            }
#endif
        }
    }
};

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
bool js_PluginGameroomJS_PluginGameroom_setListener(JSContext *cx, uint32_t argc, JS::Value *vp)
#else
bool js_PluginGameroomJS_PluginGameroom_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {

        if (!args.get(0).isObject())
        {
            ok = false;
        }

        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_setIAPListener : Error processing arguments");
        GameroomListenerJSHelper* listener = new GameroomListenerJSHelper();
        listener->setJSDelegate(cx, args.get(0));
        sdkbox::PluginGameroom::setListener(listener);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_setIAPListener : wrong number of arguments");
    return false;
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginGameroomJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginGameroom", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginGameroomJS_PluginGameroom_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#else
void register_all_PluginGameroomJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.PluginGameroom", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginGameroomJS_PluginGameroom_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginGameroomJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginGameroom", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginGameroomJS_PluginGameroom_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif

