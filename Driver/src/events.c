#pragma warning (disable : 4047 4024)
#include "../include/events.h"


PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoaded(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo) {
	UNREFERENCED_PARAMETER(ImageInfo);
	UNREFERENCED_PARAMETER(ProcessId);
	
	DbgPrint("Loaded %ls", FullImageName->Buffer);

	return STATUS_SUCCESS;
}