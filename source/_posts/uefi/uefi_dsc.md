---
title: UEFI --- dsc 语法
date: 2021/2/22
categories:
- uefi
---

---
### 语法例子
---

变量定义与判断
~~~c
DEFINE SECURE_BOOT_ENABLE      = FALSE


!if $(SECURE_BOOT_ENABLE) == TRUE
  PlatformSecureLib|OvmfPkg/Library/PlatformSecureLib/PlatformSecureLib.inf
  TpmMeasurementLib|SecurityPkg/Library/DxeTpmMeasurementLib/DxeTpmMeasurementLib.inf
  AuthVariableLib|SecurityPkg/Library/AuthVariableLib/AuthVariableLib.inf
!else
  TpmMeasurementLib|MdeModulePkg/Library/TpmMeasurementLibNull/TpmMeasurementLibNull.inf
  AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
!endif
~~~

---
### Section
---
Section的大致格式如下：[oo.xx.zz]。这里oo是必选的，而xx、zz等需要根据oo的值来确定是否存在以及具体是什么内容。下面就介绍这些常用的Section关键字。

~~~bash
[Defines]
  PLATFORM_NAME                  = LearnUefi
  PLATFORM_GUID                  = 5a9e7754-d81b-49ea-85ad-69eaa7b1539b
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/LearnUefiPkg
  SUPPORTED_ARCHITECTURES        = X64
  BUILD_TARGETS                  = NOOPT|DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = LearnUefiPkg/LearnUefiPkg.fdf
 
  #
  # Defines for default states.  These can be changed on the command line.
  # -D FLAG=VALUE
  #
  DEFINE SECURE_BOOT_ENABLE      = FALSE
  DEFINE NETWORK_IP6_ENABLE      = FALSE
  DEFINE HTTP_BOOT_ENABLE        = FALSE
  DEFINE SMM_REQUIRE             = FALSE
~~~

这个Section用来指定编译选项。EDK可以在Windows、Linux和Mac上编译，所以这里的宏也可以指定不同的系统，且EDK包含很多的语言，所以也可以指定。此外，比较特别的一点是，BIOS包含的模块有不同的类型，不同类型会对应不同的体系架构，比如PEIM需要的是32位的编译，DXE之后需要64位的编译，等等。所以这个Section还有一些变种：
~~~bash
[BuildOptions] 
[BuildOptions.common]
[BuildOptions.$(ARCH)]
[BuildOptions.common.CodeBase]
[BuildOptions.$(ARCH).CodeBase]
[BuildOptions.$(ARCH).CodeBase.$(MODULE_TYPE)]
~~~

[LibraryClasses]  
这个Section定义了所以使用到的库函数。由于库可以使用在不同的阶段和架构，所以它也分为不同的子类，如下所示：
~~~bash
[LibraryClasses]
[LibraryClasses.common]
[LibraryClasses.$(ARCH)]
[LibraryClasses.common.$(MODULE_TYPE)]
[LibraryClasses.$(ARCH).$(MODULE_TYPE) ]

越精细的范围覆盖越通用的范围
[LibraryClasses]
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
[LibraryClasses.common]
  BaseCryptLib|CryptoPkg/Library/BaseCryptLib/BaseCryptLib.inf
[LibraryClasses.common.SEC]
  TimerLib|OvmfPkg/Library/AcpiTimerLib/BaseRomAcpiTimerLib.inf
  QemuFwCfgLib|OvmfPkg/Library/QemuFwCfgLib/QemuFwCfgSecLib.inf
~~~


[PcdsXXX]
PCD的Section有不同的种类，对应不同的PCD类型，如下所示：
~~~bash 
[PcdsFeatureFlag]
[PcdsFixedAtBuild]
[PcdsDynamicDefault]
[PcdsPatchableInModule]

[PcdsFeatureFlag]
  gEfiMdeModulePkgTokenSpaceGuid.PcdHiiOsRuntimeSupport|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseMemory|TRUE
~~~

[Components]
该Section中包含所以需要编译的模块，同样由于模块的不同，这里也会对应不同的变种：
~~~bash
[Components]
[Components.common]
[Components.$(ARCH)]

[Components]
  OvmfPkg/ResetVector/ResetVector.inf
  #
  # SEC Phase modules
  #
  OvmfPkg/Sec/SecMain.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
~~~