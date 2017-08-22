#ifndef __PLUGIN_GAMEROOM_TYPES_H__
#define __PLUGIN_GAMEROOM_TYPES_H__

#include "fbg/FBG_Platform.h"

#include <string>
#include <vector>
#include <map>

#define IMPORT_TYPE(x) using x = fbg##x

namespace sdkbox {

    IMPORT_TYPE(FeedShareHandle);
    IMPORT_TYPE(AccessTokenHandle);
    IMPORT_TYPE(PurchaseHandle);
    IMPORT_TYPE(HasLicenseHandle);
	IMPORT_TYPE(AppRequestHandle);
	IMPORT_TYPE(FormDataHandle);

    IMPORT_TYPE(LoginScope);

    using FacebookID = fbid;

	using FormData = std::map<std::string, std::string>;

    //using GameroomReq = fbgRequest;

    //constants
	enum {
		SUCCESS = 0,
		FAILURE = 1,
		THREAD_SUSPEND_INTERVAL = 20,
		FBG_BUFFER_SIZE = 512
    };

	/* 
	from FBG_LoginScopes.h:

	typedef enum _fbgLoginScope {
		public_profile,
		email,
		user_friends,
		publish_actions,
		unknown
	} fbgLoginScope;
	*/
	const std::map<std::string, LoginScope> SCOPE_DICT{
		{"public_profile", public_profile}, 
		{"email", email},
		{"user_friends", user_friends}, 
		{"publish_actions", publish_actions}
	};
}
#endif