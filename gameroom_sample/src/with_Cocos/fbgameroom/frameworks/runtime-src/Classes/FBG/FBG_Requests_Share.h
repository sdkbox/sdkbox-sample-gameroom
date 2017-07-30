#ifndef FBG_REQUESTS_SHARE_H
#define FBG_REQUESTS_SHARE_H

#include "FBG_Types.h"
#include "OVR_Platform_Defs.h"

OVRP_PUBLIC_FUNCTION(fbgRequest) fbg_FeedShare(
  const char* toId,
  const char* link,
  const char* linkName,
  const char* linkCaption,
  const char* linkDescription,
  const char* pictureLink,
  const char* mediaSource
);

OVRP_PUBLIC_FUNCTION(fbgRequest) fbg_AppRequest(
  const char* message,
  const char* actionType,
  const char* objectId,
  const char* to,
  const char* filters,
  const char* excludeIDs,
  uint32_t maxRecipients,
  const char* data,
  const char* title
);



#endif
