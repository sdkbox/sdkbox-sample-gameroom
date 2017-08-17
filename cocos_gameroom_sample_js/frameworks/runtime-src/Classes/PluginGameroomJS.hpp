#ifndef __PluginGameroomJS_h__
#define __PluginGameroomJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginGameroomJS_PluginGameroom(JSContext *cx, JS::HandleObject global);
void register_all_PluginGameroomJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginGameroomJS_PluginGameroom(JSContext *cx, JSObject* global);
void register_all_PluginGameroomJS(JSContext* cx, JSObject* obj);
#endif
#endif

