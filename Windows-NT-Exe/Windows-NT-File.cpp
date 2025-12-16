// Patrick Sacchet
// File handles basic file functionality using native file functions

#include "Windows-NT-File.h"


NTSTATUS CreateAndWriteToFile(IN LPWSTR filePath, IN LPCSTR fileBuffer)
{
    NTCREATEFILE      pNtCreateFile = NULL;
    NTWRITEFILE       pNtWriteFile = NULL;
    NTCLOSE           pNtClose = NULL;
    NTSTATUS          ntStatus = 0;
    HMODULE           hNtDll;
    UNICODE_STRING    FileName;
    OBJECT_ATTRIBUTES FileAttributes;
    HANDLE            hFile;
    IO_STATUS_BLOCK   iosb;
    BYTE              Buffer[1024] = { 0 };

    // First get our handle to ntdll
    hNtDll = GetModuleHandleA("ntdll");
    if (hNtDll == NULL)
    {
        printf("Failed GetModuleHandleA; error 0x%X\n", GetLastError());
        goto cleanup;
    }

    printf("Address of ntdll: %p\n", hNtDll);

    // Then grab our functions using GetProcAddress
    pNtCreateFile = (NTCREATEFILE)GetProcAddress(hNtDll, "NtCreateFile");
    if (pNtCreateFile == NULL)
    {
        printf("Failed GetProcAddress; error 0x%X\n", GetLastError());
        goto cleanup;
    }

    printf("Address of NtCreateFile: %p\n", pNtCreateFile);

    pNtWriteFile = (NTWRITEFILE)GetProcAddress(hNtDll, "NtWriteFile");
    if (pNtWriteFile == NULL)
    {
        printf("Failed GetProcAddress; error 0x%X\n", GetLastError());
        goto cleanup;
    }

    printf("Address of NtWriteFile: %p\n", pNtWriteFile);

    pNtClose = (NTCLOSE)GetProcAddress(hNtDll, "NtClose");
    if (pNtClose == NULL)
    {
        printf("Failed GetProcAddress; error 0x%X\n", GetLastError());
        goto cleanup;
    }

    printf("Address of NtClose: %p\n", pNtClose);


    // Setup our filename buffer
    FileName.Buffer = filePath;
    FileName.Length = (USHORT)lstrlenW(filePath) * sizeof(WCHAR);
    FileName.MaximumLength = FileName.Length;

    // Setup our OBJECT_ATTRIBUTES structure
    FileAttributes.ObjectName = &FileName;
    FileAttributes.Length = sizeof(OBJECT_ATTRIBUTES);
    FileAttributes.RootDirectory = NULL;
    FileAttributes.Attributes = OBJ_OPENIF;
    FileAttributes.SecurityDescriptor = NULL;
    FileAttributes.SecurityQualityOfService = NULL;

    // Call our NtCreateFile 
    ntStatus = pNtCreateFile(&hFile, FILE_WRITE_DATA | SYNCHRONIZE, &FileAttributes, &iosb, NULL, FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_WRITE, FILE_SUPERSEDE, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
    if (ntStatus != 0)
    {
        printf("NtCreateFile failed; error 0x%X\n", ntStatus);
        goto cleanup;
    }

    // Call our NtWriteFile
    ntStatus = pNtWriteFile(hFile, NULL, NULL, NULL, &iosb, (PVOID)fileBuffer, lstrlenA(fileBuffer), NULL, NULL);
    if (ntStatus != 0)
    {
        printf("NtWriteFile failed; error 0x%X\n", ntStatus);
        goto cleanup;
    }

    // Close our file with NtCLose
    ntStatus = pNtClose(hFile);
    if (ntStatus != 0)
    {
        printf("NtClose failed; error 0x%X\n", ntStatus);
        goto cleanup;
    }


cleanup:
    return ntStatus;
}