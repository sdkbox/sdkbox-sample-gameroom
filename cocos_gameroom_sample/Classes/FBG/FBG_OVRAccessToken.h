#ifndef FBG_OVR_ACCESSTOKEN_H
#define FBG_OVR_ACCESSTOKEN_H

#include "OVR_Platform_Defs.h"

typedef struct fbgOVRAccessToken *fbgOVRAccessTokenHandle;

// Returns 0 if an invalid handle is provided.
// If provided buffer size is not large enough returns
// buffer size necessary.
// Otherwise returns the size written to the buffer.
OVRP_PUBLIC_FUNCTION(size_t) fbg_OVRAccessToken_GetTokenString(
	const fbgOVRAccessTokenHandle obj,
	char *buffer,
	size_t bufferIn
);

#endif
