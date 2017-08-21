#include "PluginGameroomJS.hpp"
#include "PluginGameroom/PluginGameroom.h"
#include "SDKBoxJSHelper.h"
#include "sdkbox/Sdkbox.h"


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 52
#elif MOZJS_MAJOR_VERSION >= 33
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS_ReportErrorUTF8(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
#else
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;
}
#endif
#elif defined(JS_VERSION)
template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    TypeTest<T> t;
    T* cobj = new T();
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    assert(p);
    JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
    js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

    return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return JS_FALSE;
}
#endif
JSClass  *jsb_sdkbox_PluginGameroom_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_PluginGameroom_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_loginWithScopes(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        unsigned int arg0;
        std::vector<std::string> arg1;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        ok &= jsval_to_std_vector_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_loginWithScopes : Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::loginWithScopes(arg0, arg1);
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_loginWithScopes : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_loginWithScopes(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 2) {
        unsigned int arg0;
        std::vector<std::string> arg1;
        ok &= jsval_to_uint32(cx, argv[0], &arg0);
        ok &= jsval_to_std_vector_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::loginWithScopes(arg0, arg1);
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 7) {
        const char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        const char* arg4;
        const char* arg5;
        const char* arg6;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        ok &= jsval_to_uint32(cx, args.get(3), &arg3);
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, args.get(4), &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, args.get(5), &arg5_tmp); arg5 = arg5_tmp.c_str();
        std::string arg6_tmp; ok &= jsval_to_std_string(cx, args.get(6), &arg6_tmp); arg6 = arg6_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL : Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::purchaseIAPWithProductURL(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 7) {
        const char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        const char* arg4;
        const char* arg5;
        const char* arg6;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_uint32(cx, argv[1], &arg1);
        ok &= jsval_to_uint32(cx, argv[2], &arg2);
        ok &= jsval_to_uint32(cx, argv[3], &arg3);
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, argv[4], &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, argv[5], &arg5_tmp); arg5 = arg5_tmp.c_str();
        std::string arg6_tmp; ok &= jsval_to_std_string(cx, argv[6], &arg6_tmp); arg6 = arg6_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::purchaseIAPWithProductURL(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_log(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_log : Error processing arguments");
        sdkbox::PluginGameroom::log(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_log : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_log(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginGameroom::log(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_hasLicense(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::hasLicense();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_hasLicense : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_hasLicense(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::hasLicense();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_payPremium(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::payPremium();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_payPremium : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_payPremium(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::payPremium();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_activateApp(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::activateApp();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_activateApp : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_activateApp(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::activateApp();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_init(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_init : Error processing arguments");
        int ret = sdkbox::PluginGameroom::init(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_init : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        int ret = sdkbox::PluginGameroom::init(arg0);
        jsval jsret;
        jsret = JS::Int32Value(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_feedShare(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 7) {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        const char* arg3;
        const char* arg4;
        const char* arg5;
        const char* arg6;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= jsval_to_std_string(cx, args.get(2), &arg2_tmp); arg2 = arg2_tmp.c_str();
        std::string arg3_tmp; ok &= jsval_to_std_string(cx, args.get(3), &arg3_tmp); arg3 = arg3_tmp.c_str();
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, args.get(4), &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, args.get(5), &arg5_tmp); arg5 = arg5_tmp.c_str();
        std::string arg6_tmp; ok &= jsval_to_std_string(cx, args.get(6), &arg6_tmp); arg6 = arg6_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_feedShare : Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::feedShare(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_feedShare : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_feedShare(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 7) {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        const char* arg3;
        const char* arg4;
        const char* arg5;
        const char* arg6;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
        std::string arg3_tmp; ok &= jsval_to_std_string(cx, argv[3], &arg3_tmp); arg3 = arg3_tmp.c_str();
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, argv[4], &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, argv[5], &arg5_tmp); arg5 = arg5_tmp.c_str();
        std::string arg6_tmp; ok &= jsval_to_std_string(cx, argv[6], &arg6_tmp); arg6 = arg6_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::feedShare(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_purchaseIAP(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 7) {
        const char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        const char* arg4;
        const char* arg5;
        const char* arg6;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
        ok &= jsval_to_uint32(cx, args.get(3), &arg3);
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, args.get(4), &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, args.get(5), &arg5_tmp); arg5 = arg5_tmp.c_str();
        std::string arg6_tmp; ok &= jsval_to_std_string(cx, args.get(6), &arg6_tmp); arg6 = arg6_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_purchaseIAP : Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::purchaseIAP(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_purchaseIAP : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_purchaseIAP(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 7) {
        const char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        const char* arg4;
        const char* arg5;
        const char* arg6;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_uint32(cx, argv[1], &arg1);
        ok &= jsval_to_uint32(cx, argv[2], &arg2);
        ok &= jsval_to_uint32(cx, argv[3], &arg3);
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, argv[4], &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, argv[5], &arg5_tmp); arg5 = arg5_tmp.c_str();
        std::string arg6_tmp; ok &= jsval_to_std_string(cx, argv[6], &arg6_tmp); arg6 = arg6_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::purchaseIAP(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_appRequest(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 9) {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        const char* arg3;
        const char* arg4;
        const char* arg5;
        unsigned int arg6;
        const char* arg7;
        const char* arg8;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= jsval_to_std_string(cx, args.get(2), &arg2_tmp); arg2 = arg2_tmp.c_str();
        std::string arg3_tmp; ok &= jsval_to_std_string(cx, args.get(3), &arg3_tmp); arg3 = arg3_tmp.c_str();
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, args.get(4), &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, args.get(5), &arg5_tmp); arg5 = arg5_tmp.c_str();
        ok &= jsval_to_uint32(cx, args.get(6), &arg6);
        std::string arg7_tmp; ok &= jsval_to_std_string(cx, args.get(7), &arg7_tmp); arg7 = arg7_tmp.c_str();
        std::string arg8_tmp; ok &= jsval_to_std_string(cx, args.get(8), &arg8_tmp); arg8 = arg8_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_PluginGameroomJS_PluginGameroom_appRequest : Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::appRequest(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_appRequest : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_appRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 9) {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        const char* arg3;
        const char* arg4;
        const char* arg5;
        unsigned int arg6;
        const char* arg7;
        const char* arg8;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
        std::string arg3_tmp; ok &= jsval_to_std_string(cx, argv[3], &arg3_tmp); arg3 = arg3_tmp.c_str();
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, argv[4], &arg4_tmp); arg4 = arg4_tmp.c_str();
        std::string arg5_tmp; ok &= jsval_to_std_string(cx, argv[5], &arg5_tmp); arg5 = arg5_tmp.c_str();
        ok &= jsval_to_uint32(cx, argv[6], &arg6);
        std::string arg7_tmp; ok &= jsval_to_std_string(cx, argv[7], &arg7_tmp); arg7 = arg7_tmp.c_str();
        std::string arg8_tmp; ok &= jsval_to_std_string(cx, argv[8], &arg8_tmp); arg8 = arg8_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        std::string ret = sdkbox::PluginGameroom::appRequest(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_isLoggedIn(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::PluginGameroom::isLoggedIn();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_isLoggedIn : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_isLoggedIn(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::PluginGameroom::isLoggedIn();
        jsval jsret;
        jsret = JS::BooleanValue(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_destroy(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = sdkbox::PluginGameroom::destroy();
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_destroy : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_destroy(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        int ret = sdkbox::PluginGameroom::destroy();
        jsval jsret;
        jsret = JS::Int32Value(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginGameroomJS_PluginGameroom_login(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::login();
        JS::RootedValue jsret(cx);
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginGameroomJS_PluginGameroom_login : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginGameroomJS_PluginGameroom_login(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::string ret = sdkbox::PluginGameroom::login();
        jsval jsret;
        sdkbox::c_string_to_jsval(cx, ret.c_str(), &jsret, ret.size());
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginGameroomJS_PluginGameroom_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginGameroom)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGameroomJS_PluginGameroom(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "PluginGameroom",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_PluginGameroom_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_PluginGameroom_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginGameroom_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginGameroom_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginGameroom_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginGameroom_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginGameroom_class->finalize = js_PluginGameroomJS_PluginGameroom_finalize;
    jsb_sdkbox_PluginGameroom_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("loginWithScopes", js_PluginGameroomJS_PluginGameroom_loginWithScopes, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("purchaseIAPWithProductURL", js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("log", js_PluginGameroomJS_PluginGameroom_log, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasLicense", js_PluginGameroomJS_PluginGameroom_hasLicense, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("payPremium", js_PluginGameroomJS_PluginGameroom_payPremium, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("activateApp", js_PluginGameroomJS_PluginGameroom_activateApp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginGameroomJS_PluginGameroom_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("feedShare", js_PluginGameroomJS_PluginGameroom_feedShare, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("purchaseIAP", js_PluginGameroomJS_PluginGameroom_purchaseIAP, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appRequest", js_PluginGameroomJS_PluginGameroom_appRequest, 9, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoggedIn", js_PluginGameroomJS_PluginGameroom_isLoggedIn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("destroy", js_PluginGameroomJS_PluginGameroom_destroy, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("login", js_PluginGameroomJS_PluginGameroom_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_PluginGameroom_class,
        dummy_constructor<sdkbox::PluginGameroom>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::PluginGameroom>(cx, jsb_sdkbox_PluginGameroom_class, proto);
#else
    jsb_register_class<sdkbox::PluginGameroom>(cx, jsb_sdkbox_PluginGameroom_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::PluginGameroom> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginGameroom_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "PluginGameroom");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginGameroomJS_PluginGameroom(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginGameroom_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginGameroom_class->name = "PluginGameroom";
    jsb_sdkbox_PluginGameroom_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginGameroom_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginGameroom_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginGameroom_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginGameroom_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginGameroom_class->finalize = js_PluginGameroomJS_PluginGameroom_finalize;
    jsb_sdkbox_PluginGameroom_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("loginWithScopes", js_PluginGameroomJS_PluginGameroom_loginWithScopes, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("purchaseIAPWithProductURL", js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("log", js_PluginGameroomJS_PluginGameroom_log, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasLicense", js_PluginGameroomJS_PluginGameroom_hasLicense, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("payPremium", js_PluginGameroomJS_PluginGameroom_payPremium, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("activateApp", js_PluginGameroomJS_PluginGameroom_activateApp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginGameroomJS_PluginGameroom_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("feedShare", js_PluginGameroomJS_PluginGameroom_feedShare, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("purchaseIAP", js_PluginGameroomJS_PluginGameroom_purchaseIAP, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appRequest", js_PluginGameroomJS_PluginGameroom_appRequest, 9, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoggedIn", js_PluginGameroomJS_PluginGameroom_isLoggedIn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("destroy", js_PluginGameroomJS_PluginGameroom_destroy, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("login", js_PluginGameroomJS_PluginGameroom_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginGameroom_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginGameroom_class,
        dummy_constructor<sdkbox::PluginGameroom>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "PluginGameroom", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginGameroom> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginGameroom_class;
        p->proto = jsb_sdkbox_PluginGameroom_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginGameroomJS_PluginGameroom(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginGameroom_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginGameroom_class->name = "PluginGameroom";
    jsb_sdkbox_PluginGameroom_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginGameroom_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginGameroom_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginGameroom_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginGameroom_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginGameroom_class->finalize = js_PluginGameroomJS_PluginGameroom_finalize;
    jsb_sdkbox_PluginGameroom_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("loginWithScopes", js_PluginGameroomJS_PluginGameroom_loginWithScopes, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("purchaseIAPWithProductURL", js_PluginGameroomJS_PluginGameroom_purchaseIAPWithProductURL, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("log", js_PluginGameroomJS_PluginGameroom_log, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasLicense", js_PluginGameroomJS_PluginGameroom_hasLicense, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("payPremium", js_PluginGameroomJS_PluginGameroom_payPremium, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("activateApp", js_PluginGameroomJS_PluginGameroom_activateApp, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginGameroomJS_PluginGameroom_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("feedShare", js_PluginGameroomJS_PluginGameroom_feedShare, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("purchaseIAP", js_PluginGameroomJS_PluginGameroom_purchaseIAP, 7, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appRequest", js_PluginGameroomJS_PluginGameroom_appRequest, 9, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoggedIn", js_PluginGameroomJS_PluginGameroom_isLoggedIn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("destroy", js_PluginGameroomJS_PluginGameroom_destroy, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("login", js_PluginGameroomJS_PluginGameroom_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginGameroom_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginGameroom_class,
        dummy_constructor<sdkbox::PluginGameroom>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "PluginGameroom", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginGameroom> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_PluginGameroom_class;
        p->proto = jsb_sdkbox_PluginGameroom_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginGameroomJS(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "sdkbox", &ns);

    js_register_PluginGameroomJS_PluginGameroom(cx, ns);

    //sdkbox::setProjectType("js");
}
#else
void register_all_PluginGameroomJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginGameroomJS_PluginGameroom(cx, obj);

    //sdkbox::setProjectType("js");
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginGameroomJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginGameroomJS_PluginGameroom(cx, obj);

    //sdkbox::setProjectType("js");
}
#endif