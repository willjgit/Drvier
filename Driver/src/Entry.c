#include "../include/Entry.h"
#include "../include/events.h"

VOID Unload(IN PDRIVER_OBJECT driverObject) {
	DbgPrint("Unloaded");
	PsRemoveLoadImageNotifyRoutine(ImageLoaded);
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath) {
	driverObject->DriverUnload = Unload;
	PsSetLoadImageNotifyRoutine(ImageLoaded);

	DbgPrint("Hello World");
	return STATUS_SUCCESS;

}