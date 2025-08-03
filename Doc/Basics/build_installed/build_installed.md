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