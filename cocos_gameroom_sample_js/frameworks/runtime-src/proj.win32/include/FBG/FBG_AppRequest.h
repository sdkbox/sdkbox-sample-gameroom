#ifndef FBG_APP_REQUEST_H
#define FBG_APP_REQUEST_H

#include "OVR_Platform_Defs.h"
#include "FBG_Types.h"
#include <stddef.h>

typedef struct fbgAppRequest *fbgAppRequestHandle;

// Returns 0 if an invalid handle is provided.
// If provided buffer size is not large enough returns
// buffer size necessary.
// Otherwise returns the size written to the buffer.
OVRP_PUBLIC_FUNCTION(size_t) fbg_AppRequest_GetRequestObjectId(
  const fbgAppRequestHandle obj,
  char *buffer,
  size_t bufferIn
);

// Returns 0 if an invalid handle is provided.
// If provided buffer size is not large enough returns
// buffer size necessary.
// Otherwise returns the size written to the buffer.
OVRP_PUBLIC_FUNCTION(size_t) fbg_AppRequest_GetTo(
  const fbgAppRequestHandle obj,
  char *buffer,
  size_t bufferIn
);

#endif
