#pragma once
#include "PluginGameroom.h"

class GameListener : public sdkbox::GameroomListener {
public:
	GameListener() = default;
	~GameListener() = default;

public:
	virtual void onLoginAccessTokenMsg(fbgAccessTokenHandle);
	virtual void onFeedShareMsg(fbgFeedShareHandle);
	virtual void onPurchaseIAPMsg(fbgPurchaseHandle);
	virtual void onPurchaseTrialware(fbgHasLicenseHandle);

};