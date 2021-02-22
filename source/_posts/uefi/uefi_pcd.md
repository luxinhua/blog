---
title: UEFI --- PCD 语法
date: 2021/2/22
categories:
- uefi
---

---
### PCD
---
~~~bash
TokenSpaceGuidCName.PcdCName
~~~
TokenSpaceGuidCName是一个GUID，PcdCName是一个变量名，两者合起来构成了唯一的PCD变量

PCD 变量有如下类型 （ 主要是访问方式不同 ）：
* FeatureFlag PCD：它最终返回的是一个TRUE或者FALSE，用于判断条件中；
~~~bash
[PcdsFeatureFlag]
  gUefiOemPkgTokenSpaceGuid.PcdTestFeatureVar|FALSE|BOOLEAN|0x30000001

访问： 
DEBUG ((EFI_D_ERROR, "[beni]PcdTestBooleanVar: %d\n", FeaturePcdGet (PcdTestFeatureVar)));
DEBUG ((EFI_D_ERROR, "[beni]PcdTestBooleanVar: %d\n", PcdGetBool (PcdTestFeatureVar)));
~~~
* PatchableInModule PCD：这种变量的值可以在编译的时候确定，这个不算特别，特别的是它可以在编译完成的二进制文件上通过工具来修改值；
~~~bash
[PcdsPatchableInModule]
gUefiOemPkgTokenSpaceGuid.PcdPatchableVar|0x00ABCDEF|UINT32|0x50000001

DEBUG ((EFI_D_ERROR, "[beni]PcdPatchableVar: 0x%x\n", PcdGet32 (PcdPatchableVar)));
~~~

* FixedAtBuild PCD：静态值，在编译的时候确定，整个UEFI阶段不可变；
~~~
[PcdsFixedAtBuild]
gUefiOemPkgTokenSpaceGuid.PcdTestVar1|0xA5|UINT8|0x20000001
gUefiOemPkgTokenSpaceGuid.PcdTestVar2|0xA5A5|UINT16|0x20000002
gUefiOemPkgTokenSpaceGuid.PcdTestVar3|0xA5A5A5A5|UINT32|0x20000003
gUefiOemPkgTokenSpaceGuid.PcdTestVar4|0xA5A5A5A5A5A5A5A5|UINT64|0x20000004

访问： 
DEBUG ((EFI_D_ERROR, "[beni]PcdTestVar1: 0x%x.\n", PcdGet8 (PcdTestVar1)));
DEBUG ((EFI_D_ERROR, "[beni]PcdTestVar2: 0x%x.\n", PcdGet16 (PcdTestVar2)));
DEBUG ((EFI_D_ERROR, "[beni]PcdTestVar3: 0x%x.\n", PcdGet32 (PcdTestVar3)));
DEBUG ((EFI_D_ERROR, "[beni]PcdTestVar4: 0x%x.\n", PcdGet64 (PcdTestVar4)));
~~~
* Dynamic PCD：前面的三种类型可以认为是静态的PCD，而这里以及之后的是动态的PCD；它的特点是可以在UEFI运行的过程中通过Set宏来修改值；在《edk-ii-build-specification.pdf》中有说明该种类型的PCD必须在DSC中在列一遍，但是实际使用似乎并不是必须的；
~~~bash 
[PcdsDynamic]
gUefiOemPkgTokenSpaceGuid.PcdOemVersion|0xABCDDCBA|UINT32|0x40000001

DEBUG ((EFI_D_ERROR, "[beni]PcdOemVersion: 0x%x\n", PcdGet32 (PcdOemVersion)));
~~~
* DynamicEx PCD：跟Dynamic PCD类似，算是加强版，使用宏PcdGetEx/PcdSetEx来访问变量；

PCD变量值的类型： 
* BOOLEAN类型
* 整型（UINT8，UINT16等）
* VOID *类型

example : 
~~~bash
[PcdsDynamic]
  gUefiOemPkgTokenSpaceGuid.PcdOemVersion|0xFFFFFFFF|UINT32|0x40000001
~~~
* PcdsDynamic PCD类型
* PcdOemVersion PCD变量名
* 0xFFFFFFFF default 值
* UINT32 类型
* 0x40000001  token--> Token是一个32位的整型，在DEC中每个PCD都有一个独一无二的Token



PCD 读写值: 
~~~bash
PcdGet32(PcdOemVersion))
~~~
要使用读写函数，需要依赖pcd.inf模块：

Pcd.inf模块分为PEI和DXE两个版本，分别放在PEI阶段和DXE阶段的最前面，只有整个模块初始化完成之后，才能够开始正常使用PCD宏来访问Dynamic PCD变量。

以DXE阶段的Pcd.inf模块为例，它主要做了两件事情：

1. 初始化该阶段使用的PCD数据库；

2. 安装各种处理PCD需要的Protocol；

可能用到的protocol:
~~~c
///
/// This service abstracts the ability to set/get Platform Configuration Database (PCD).
///
typedef struct {
  PCD_PROTOCOL_SET_SKU              SetSku;
 
  PCD_PROTOCOL_GET8                 Get8;
  PCD_PROTOCOL_GET16                Get16;
  PCD_PROTOCOL_GET32                Get32;
  PCD_PROTOCOL_GET64                Get64;
  PCD_PROTOCOL_GET_POINTER          GetPtr;
  PCD_PROTOCOL_GET_BOOLEAN          GetBool;
  PCD_PROTOCOL_GET_SIZE             GetSize;
 
  PCD_PROTOCOL_GET_EX_8             Get8Ex;
  PCD_PROTOCOL_GET_EX_16            Get16Ex;
  PCD_PROTOCOL_GET_EX_32            Get32Ex;
  PCD_PROTOCOL_GET_EX_64            Get64Ex;
  PCD_PROTOCOL_GET_EX_POINTER       GetPtrEx;
  PCD_PROTOCOL_GET_EX_BOOLEAN       GetBoolEx;
  PCD_PROTOCOL_GET_EX_SIZE          GetSizeEx;
 
  PCD_PROTOCOL_SET8                 Set8;
  PCD_PROTOCOL_SET16                Set16;
  PCD_PROTOCOL_SET32                Set32;
  PCD_PROTOCOL_SET64                Set64;
  PCD_PROTOCOL_SET_POINTER          SetPtr;
  PCD_PROTOCOL_SET_BOOLEAN          SetBool;
 
  PCD_PROTOCOL_SET_EX_8             Set8Ex;
  PCD_PROTOCOL_SET_EX_16            Set16Ex;
  PCD_PROTOCOL_SET_EX_32            Set32Ex;
  PCD_PROTOCOL_SET_EX_64            Set64Ex;
  PCD_PROTOCOL_SET_EX_POINTER       SetPtrEx;
  PCD_PROTOCOL_SET_EX_BOOLEAN       SetBoolEx;
 
  PCD_PROTOCOL_CALLBACK_ONSET       CallbackOnSet;
  PCD_PROTOCOL_CANCEL_CALLBACK      CancelCallback;
  PCD_PROTOCOL_GET_NEXT_TOKEN       GetNextToken;
  PCD_PROTOCOL_GET_NEXT_TOKENSPACE  GetNextTokenSpace;
} PCD_PROTOCOL;
~~~








