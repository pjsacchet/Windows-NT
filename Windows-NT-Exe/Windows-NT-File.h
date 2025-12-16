#pragma once

#include "Windows-NT-Exe.h"

// Define our primitives for Nt file functions 
typedef NTSTATUS(WINAPI* NTCREATEFILE)(OUT PHANDLE FileHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PLARGE_INTEGER AllocationSize OPTIONAL,
    IN ULONG FileAttributes,
    IN ULONG ShareAccess,
    IN ULONG CreateDisposition,
    IN ULONG CreateOptions,
    IN PVOID EaBuffer OPTIONAL,
    IN ULONG EaLength);

typedef NTSTATUS(WINAPI* NTWRITEFILE)(IN HANDLE FileHandle,
    IN HANDLE Event OPTIONAL,
    IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
    IN PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    OUT PVOID Buffer,
    IN ULONG Length,
    IN PLARGE_INTEGER ByteOffset OPTIONAL,
    IN PULONG Key OPTIONAL);

typedef NTSTATUS(WINAPI* NTCLOSE)(IN HANDLE Handle);

NTSTATUS CreateAndWriteToFile(IN LPWSTR filePath, IN LPCSTR fileBuffer);
