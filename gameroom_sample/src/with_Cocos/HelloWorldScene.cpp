#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
        winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*) {
        auto l = sdkbox::PluginGameroom::listener();
        sdkbox::PluginGameroom::destroy();
        delete l;
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
        -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::createTestMenu()
{
    sdkbox::PluginGameroom::setListener(this);

    auto menu = Menu::create();
    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom User Login", "sans", 24), [](Ref*) {
        CCLOG("Gameroom User Login");
        //sdkbox::PluginAppodeal::showAd(sdkbox::PluginAppodeal::AppodealShowStyleInterstitial);

        sdkbox::LoginScope loginScopes[2] = { sdkbox::LoginScope::user_friends, sdkbox::LoginScope::email };
        sdkbox::PluginGameroom::loginWithScopes(
            2,
            loginScopes
        );
    }));

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom Check Login ", "sans", 24), [](Ref*) {
        CCLOG("Gameroom Check Login");
        sdkbox::PluginGameroom::isLoggedIn();
    }));

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom Feed Share", "sans", 24), [](Ref*) {
        CCLOG("Gameroom Feed Share");
        sdkbox::PluginGameroom::feedShare(
            nullptr,
            "https://www.facebook.com",
            "Testing Link Name",
            "Testing Link Caption",
            "Testing Link Description",
            "http://www.pamperedpetz.net/wp-content/uploads/2015/09/Puppy1.jpg",
            nullptr
        );
    }));

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom IAP", "sans", 24), [](Ref*) {
        CCLOG("Gameroom IAP");
        sdkbox::PluginGameroom::purchaseIAP(
            "coins200",
            1,
            1,
            1,
            nullptr,
            nullptr,
            nullptr
        );
    }));

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom IAP with Product Link", "sans", 24), [](Ref*) {
        CCLOG("Gameroom IAP with Product Link");
        sdkbox::PluginGameroom::purchaseIAPWithProductURL(
            "https://friendsmash-unity.herokuapp.com/payments/100coins.php",
            1,
            1,
            1,
            nullptr,
            nullptr,
            nullptr
        );
    }));

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom Purchase License or Premium", "sans", 24), [](Ref*) {
        CCLOG("Gameroom Purchase License or Premium");
        sdkbox::PluginGameroom::payPremium();
    }));

    menu->addChild(MenuItemLabel::create(Label::createWithSystemFont("Gameroom Check License ", "sans", 24), [](Ref*) {
        CCLOG("Gameroom Check License");
        sdkbox::PluginGameroom::hasLicense();
    }));

    menu->alignItemsVerticallyWithPadding(10);
    addChild(menu);
}

void HelloWorld::onLoginAccessTokenMsg(fbgAccessTokenHandle accessTokenHandle) {
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

    ::CCLOG(
        "User ID: %lld\nAccess Token: %s\nExpiration Timestamp: %lld, Permission Count: %zu\nPermissions: ",
        (long long)userid,
        token_string,
        (long long)expiration_timestamp,
        permissionCount
    );

    for (size_t i = 0; i < permissionCount; i++) {
        ::CCLOG("%s", sdkbox::PluginGameroom::loginScopeToString(permissions[i]));
    }
    ::CCLOG("\n");
}

void HelloWorld::onFeedShareMsg(fbgFeedShareHandle feedShareHandle) {
    auto postId = sdkbox::PluginGameroom::feedShareGetPostID(feedShareHandle);
    ::CCLOG(
        "Feed Share Post ID: %ld\n",
        (long)postId
    );
}

void HelloWorld::onPurchaseIAPMsg(fbgPurchaseHandle payHandle) {
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

    ::CCLOG(
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

void HelloWorld::onPurchaseTrialware(fbgHasLicenseHandle hasLicenseHandle) {
    auto hasLicense = sdkbox::PluginGameroom::purchaseGetLicense(hasLicenseHandle);
    ::CCLOG(
        "Has License: %llu",
        hasLicense
    );
}