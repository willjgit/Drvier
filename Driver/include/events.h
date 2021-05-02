#pragma once
#include <ntifs.h>

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoaded(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo);