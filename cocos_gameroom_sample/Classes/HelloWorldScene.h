#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PluginGameroom.h"

class HelloWorld : public cocos2d::Scene, public sdkbox::GameroomListener
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void createTestMenu();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void onLoginAccessTokenMsg(sdkbox::AccessTokenHandle);
    virtual void onFeedShareMsg(sdkbox::FeedShareHandle);
    virtual void onPurchaseIAPMsg(sdkbox::PurchaseHandle);
    virtual void onHasLicenseMsg(sdkbox::HasLicenseHandle);
	virtual void onAppRequestMsg(sdkbox::AppRequestHandle);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
