#pragma once
#include <ntifs.h>

VOID Unload(IN PDRIVER_OBJECT driverObject);
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath);

NTSTATUS Control(PDEVICE_OBJECT DeviceObj, PIRP Irp);
NTSTATUS Create(PDEVICE_OBJECT DeviceObj, PIRP Irp);
NTSTATUS Close(PDEVICE_OBJECT DeviceObject, PIRP irp);



UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\KernelGod");
UNICODE_STRING DeviceLink = RTL_CONSTANT_STRING(L"\\??\\KernelGod");

PDEVICE_OBJECT DeviceObj = NULL;