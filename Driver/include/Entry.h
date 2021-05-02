#pragma once
#include <ntifs.h>

VOID Unload(IN PDRIVER_OBJECT driverObject);
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath);