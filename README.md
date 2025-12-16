# Windows-NT
Exploring exported functions via NTDLL

## Why it Matters
By utilizing the Native API, offensive developers can help obfuscate their code with lower level calls to user mode/kernel mode. These Native APIs are less subject to parameter checking and validation, and additionally, offer a lot more when it comes to available parameters to pass to the kernel. Additionally, we can dynamically link at run-time, making detection overall more difficult for defenders. 

## Three Main Points
1. Implant development is increasingly difficult on Windows platforms thanks to increasingly complex and effective anti-virus and EDR solutions being installed
2. The Native API allows close kernel level development while still operating in user mode; creating an accessible yet effective way of developing operations on target
3. Several features of the Native API make it more obfuscated, difficult to detect, and at the same time, more accessible to developers who are offensively inclined 

## File APIs
### NtCreateFile
https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntcreatefile

### NtWriteFile
https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntwritefile

### NtClose
https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntclose

### Sample Output 
```
PS C:\Users\Patrick Sacchet\Projects\Personal\Windows-NT\Windows-NT-Exe\x64\Debug> .\Windows-NT-Exe.exe
Address of ntdll: 00007FF99A0A0000
Address of NtCreateFile: 00007FF99A202650
Address of NtWriteFile: 00007FF99A201CB0
Address of NtClose: 00007FF99A201D90
Successfully created and wrote to file!
```

## References
- https://www.geoffchappell.com/studies/windows/win32/ntdll/api/native.htm
- https://www.geoffchappell.com/studies/windows/win32/ntdll/index.htm#:~:text=NTDLL%20is%20the%20user%2Dmode,DLL%20and%20ADVAPI32.
- https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/
- https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwcreatefile
- https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
