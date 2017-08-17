#ifndef FBG_ERROR_RESPONSE_H
#define FBG_ERROR_RESPONSE_H

#include "FBG_ErrorType.h"
#include "FBG_MessageType.h"
#include "FBG_Types.h"
#include "OVR_Platform_Defs.h"

typedef struct fbgError *fbgErrorHandle;

// Gets the request message type that caused the error
OVRP_PUBLIC_FUNCTION(fbgMessageType) fbg_Error_GetMessageType(const fbgErrorHandle obj);
OVRP_PUBLIC_FUNCTION(fbgErrorType) fbg_Error_GetErrorType(const fbgErrorHandle obj);

// Returns 0 if an invalid handle is provided.
// If provided buffer size is not large enough returns
// buffer size necessary.
// Otherwise returns the size written to the buffer.
OVRP_PUBLIC_FUNCTION(size_t) fbg_Error_GetErrorMessage(const fbgErrorHandle obj, char *buffer, size_t bufferIn);

#endif
