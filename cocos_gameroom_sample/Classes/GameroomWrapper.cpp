#include <cassert>
#include <functional>

#include "GameroomWrapper.h"

#include <map>

namespace sdkbox {

    HANDLE GameroomWrapper::thHandle_ = nullptr;
    bool GameroomWrapper::isRunning_ = false;
    GameroomListener* GameroomWrapper::listener_ = nullptr;

    int GameroomWrapper::init() {
        if (isRunning_) {
            return SUCCESS;
        }

        isRunning_ = true;
        return createPluginThread();
    }

    int GameroomWrapper::destroy() {

        isRunning_ = false;
        
        HANDLE h[1]{ thHandle_ };
        if (WaitForMultipleObjects(1, h, TRUE, INFINITE) == 0xFFFFFFFF) {
            return FAILURE;
        }
        listener_ = nullptr;
        thHandle_ = nullptr;

        return SUCCESS;
    }

    int GameroomWrapper::setListener(GameroomListener* l) {
        listener_ = l;
        return SUCCESS;
    }

    GameroomListener* GameroomWrapper::removeListener() {
        auto l = listener_;
        listener_ = nullptr;
        return l;
    }

    GameroomListener * GameroomWrapper::listener() {
        return listener_;
    }

	std::string GameroomWrapper::loginWithScopes(uint32_t scopeCount, const std::vector<std::string>& loginScopes) {
		LoginScope scopes[FBG_BUFFER_SIZE];
		auto extractedScopesCount = extractLoginScopes(loginScopes, scopes);
		if (extractedScopesCount != scopeCount) {
			scopeCount = extractedScopesCount;
		}
		auto ret = fbg_Login_WithScopes(scopeCount, scopes);

		return std::to_string(ret);
	}

    int GameroomWrapper::createPluginThread() {
        thHandle_ = CreateThread(NULL, 0, pluginThreadFunc, NULL, 0, NULL);
        if (thHandle_ == nullptr) {
            return FAILURE;
        }

        return SUCCESS;
    }

    DWORD GameroomWrapper::pluginThreadFunc(LPVOID arg) {
        fbgMessageHandle message = nullptr;

        while (isRunning_) {
            while ((message = fbg_PopMessage()) != nullptr) {
                if (listener_ == nullptr) {
                    continue;
                }
                switch (fbg_Message_GetType(message)) {
                case fbgMessage_AccessToken:
                {
                    auto accessTokenHandle = fbg_Message_AccessToken(message);
                    listener_->onLoginAccessTokenMsg(accessTokenHandle);
                    break;
                }

                case fbgMessage_FeedShare:
                {
                    auto feedShareHandle = fbg_Message_FeedShare(message);
                    listener_->onFeedShareMsg(feedShareHandle);
                    break;
                }

                case fbgMessage_Purchase:
                {
                    auto payHandle = fbg_Message_Purchase(message);
                    listener_->onPurchaseIAPMsg(payHandle);
                    break;
                }

                case fbgMessage_HasLicense:
                {
                    auto hasLicenseHandle = fbg_Message_HasLicense(message);
                    listener_->onPurchaseTrialware(hasLicenseHandle);
                    break;
                }

                default:
                    fprintf(stderr, "unknown message %d", fbg_Message_GetType(message));
                    assert(false);
                }
                fbg_FreeMessage(message);
            }
            Sleep(THREAD_SUSPEND_INTERVAL);
        }

        return SUCCESS;
    }
	uint32_t GameroomWrapper::extractLoginScopes(const std::vector<std::string>& loginScopes, LoginScope * scopes) {
		uint32_t i = 0; 
		for (auto s : loginScopes) {
			if (SCOPE_DICT.count(s) > 0) {
				scopes[i++] = SCOPE_DICT.at(s);
			}
		}

		return i;
	}
}