// Patrick Sacchet
// Main entry point for execution

#include "Windows-NT-Exe.h"
#include "Windows-NT-File.h"


int main()
{
    NTSTATUS status = 0;
    LPWSTR fileName = (wchar_t*)L"\\??\\c:\\test\\test.txt";
    LPCSTR fileBuffer = "this is a test";

    status = CreateAndWriteToFile(fileName, fileBuffer);
    if (status != 0)
    {
        printf("Failed CreateAndWriteToFile; error 0x%X\n", status);
        return -1;
    }

    printf("Successfully created and wrote to file!\n");

    return 0;
}

