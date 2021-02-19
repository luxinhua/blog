---
title: UEFI hello world 模块
date: 2021/2/7
categories:
- uefi
---

---
### 目的
---
EFI shell 中运行 helloworld.efi，执行我们写的驱动



---
### c文件
---
放在某个pkg下: OvmfPkg\HelloWorld\HelloWorld.c
~~~c
#include <uefi.h> 
#include <Library/UefiLib.h> 
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

//ShellCEntryLib call user interface ShellAppMain
EFI_STATUS
EFIAPI
HelloWorldEntry(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{   
  EFI_STATUS  Status = EFI_SUCCESS;
  Print (L"[Console]  HelloWorldEntry Start..\n");
  
  Print (L"[Console]  HelloWorldEntry  End ... \n"); 
  return Status;
}
~~~

同级目录下添加构建文件 ：OvmfPkg\HelloWorld\HelloWorld.inf
~~~bash
  INF_VERSION = 0x00010007 
  BASE_NAME = HelloWorld
  FILE_GUID = 69A6DE6D-FA9F-485E-9A4E-EA70FDCFD82F
  MODULE_TYPE = UEFI_APPLICATION
  VERSION_STRING = 1.0
  ENTRY_POINT = HelloWorldEntry 
  
[Sources] 
  HelloWorld.c 
  
[Packages]
  MdePkg/MdePkg.dec
  ShellPkg/ShellPkg.dec 
  MdeModulePkg/MdeModulePkg.dec
  
[LibraryClasses]
  UefiShellCEntryLib
  BaseLib
  BaseMemoryLib
  DebugLib
  PrintLib
  UefiBootServicesTableLib
  MemoryAllocationLib
  UefiLib
~~~

在项目对应的DSC中添加如下内容：OvmfPkg\OvmfPkgX64.dsc
~~~bash
...
[Components]
  OvmfPkg/HelloWorld/HelloWorld.inf
...
~~~

此时编译整个项目就可以编译到我们的模块
运行edksetup.bat编译整个OvmfPkg Package
build -a X64 -p OvmfPkg\OvmfPkgX64.dsc -D DEBUG_ON_SERIAL_PORT