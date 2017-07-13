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

    virtual void onLoginAccessTokenMsg(fbgAccessTokenHandle);
    virtual void onFeedShareMsg(fbgFeedShareHandle);
    virtual void onPurchaseIAPMsg(fbgPurchaseHandle);
    virtual void onPurchaseTrialware(fbgHasLicenseHandle);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
