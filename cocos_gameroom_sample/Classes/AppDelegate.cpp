#include "AppDelegate.h"
#include "HelloWorldScene.h"

#ifdef SDKBOX_ENABLED
#include "PluginGameroom.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {
	freopen("fbg.log", "w", stdout);
}

AppDelegate::~AppDelegate()
{
	fclose(stdout);
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
#ifdef SDKBOX_ENABLED
    //sdkbox::PluginGameroom::init("523164037733626");
	sdkbox::PluginGameroom::init("313416692430467");
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	if (!glview) {
		const wchar_t title[]{ L"Facebook Gameroom" };
		auto parentWin = FindWindow(NULL, title);
		::CCLOG("parent HWND: %x", parentWin);
		
		// set dpi for app.
		auto res_dpi = SetProcessDPIAware();
		::CCLOG("set dpi result: %u", res_dpi);

		RECT rect; 
		GetWindowRect(parentWin, &rect);
		::CCLOG("Parent Rect Size: %d, %d, %d, %d", rect.top, rect.left, rect.right, rect.bottom);
		::CCLOG("parent window size: %d, %d", rect.right - rect.left, rect.bottom - rect.top);
        glview = GLViewImpl::createWithRect("facebook", Rect(0, 0, rect.right - rect.left - 20, rect.bottom - rect.top - 100), 1.0f, true);
        director->setOpenGLView(glview);
		auto currentWin = Director::getInstance()->getOpenGLView()->getWin32Window();
		::CCLOG("current HWND: %x", currentWin);
		SetParent(currentWin, parentWin);
    }

    auto framesize = director->getOpenGLView()->getFrameSize();
    director->getOpenGLView()->setDesignResolutionSize(framesize.width, framesize.height, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
