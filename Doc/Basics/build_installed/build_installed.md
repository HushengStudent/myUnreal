### [部署虚幻引擎](https://dev.epicgames.com/documentation/zh-cn/unreal-engine/create-an-installed-build-of-unreal-engine?application_version=5.5)

**BuildGraph**：UE的自动化构建系统

**主脚本**：InstalledEngineBuild.xml（UE的预置安装包构建脚本）

**主目标**：Make Installed Build Win64（生成Win64安装包）

```language
UnrealEngine-5.4.4-release\Engine\Build\BatchFiles\RunUAT.bat BuildGraph 
-script=Engine/Build/InstalledEngineBuild.xml 
-target="Make Installed Build Win64" 
-nosign 
-set:GameConfigurations=Development;Shipping 
-set:WithWin64=true 
-set:WithAndroid=false 
-set:WithDDC=false 
-set:WithLinux=false 
-set:WithLinuxArm64=false 
-set:WithIOS=false 
-set:WithTVOS=false 
-set:WithMac=false 
-clean
```

注册

```language
Windows Registry Editor Version 5.00

[HKEY_CURRENT_USER\SOFTWARE\Epic Games\UnrealEngine\Builds\MyCustom419]
@="D:\\CustomUE"
```

#### 问题：

Unable to find installation of PDBCOPY.EXE, which is required to strip symbols. This tool is included as part of the 'Windows Debugging Tools' component of the Windows 10 SDK (https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk).

C:\Program Files (x86)\Windows Kits\10\Debuggers\x64里面确实没pdbcopy.exe

打开 "控制面板"→"程序和功能"

找到已安装的 "Windows Software Development Kit"

右键选择 "更改"→"修改"

在组件列表中勾选 "Debugging Tools for Windows"