#pragma once

#include "debug/log.h"
#include "DAdbg/DAdbg.h"

#define cLOG(severity, message)  daLOG(severity, message)
#define cLOG_CRITICAL(message)   daLOG_CRITICAL(message)
#define cLOG_ERROR(message)      daLOG_ERROR(message)
#define cLOG_WARN(message)       daLOG_WARN(message)
#define cLOG_INFO(message)       daLOG_INFO(message)
#define cLOG_TRACE(message)      daLOG_TRACE(message)

#define cVERSION              "v0.0.1a"