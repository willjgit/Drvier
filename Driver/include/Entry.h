#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>

#define READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x333,METHOD_BUFFERED,FILE_SPECIAL_ACCESS)
#define DLL_ADDR_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x334,METHOD_BUFFERED,FILE_SPECIAL_ACCESS)
#define PROC_ID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x335,METHOD_BUFFERED,FILE_SPECIAL_ACCESS)

#define Print(thing,...) DbgPrintEx(0,0,thing,__VA_ARGS__)


NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);



VOID Unload(IN PDRIVER_OBJECT driverObject);
NTSTATUS DriverEntry(IN PDRIVER_OBJECT driverObject, IN PCUNICODE_STRING registryPath);

NTSTATUS Control(PDEVICE_OBJECT DeviceObj, PIRP Irp);
NTSTATUS Create(PDEVICE_OBJECT DeviceObj, PIRP Irp);
NTSTATUS Close(PDEVICE_OBJECT DeviceObject, PIRP irp);


NTSTATUS ReadMemoryKernel(PEPROCESS proc, PVOID src, PVOID target, SIZE_T size);

typedef struct _K_READ_REQUEST {
	ULONG ProcId;
	ULONG Addr;
	PVOID Buff;
	ULONG Size;
}K_READ_REQUEST,*PK_READ_REQUEST;


UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\KernelGod");
UNICODE_STRING DeviceLink = RTL_CONSTANT_STRING(L"\\??\\KernelGod");

PDEVICE_OBJECT DeviceObj = NULL;