#pragma once
#include "fbg/FBG_Platform.h"

#define IMPORT_TYPE(x) using x = fbg##x

namespace sdkbox {

    IMPORT_TYPE(FeedShareHandle);
    IMPORT_TYPE(AccessTokenHandle);
    IMPORT_TYPE(PurchaseHandle);
    IMPORT_TYPE(HasLicenseHandle);

    IMPORT_TYPE(LoginScope);

    using FacebookID = fbid;

    using GameroomReq = fbgRequest;

    //constants
    enum {
        SUCCESS = 0,
        FAILURE = 1,
        THREAD_SUSPEND_INTERVAL = 20
    };
}