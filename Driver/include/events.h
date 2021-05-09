#pragma once
#include <ntifs.h>

#define Print(thing,...) DbgPrintEx(0,0,thing,__VA_ARGS__)


ULONG DLLAdress;
ULONG procID;
PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoaded(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo);