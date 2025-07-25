#### 1、生成项目文件

导航到 Unreal Engine 源码目录。

运行Setup.bat脚本。这个脚本会下载必要的依赖文件，如第三方库等。这可能需要一些时间，具体取决于你的网络速度。

运行GenerateProjectFiles.bat。这个脚本会根据你的系统配置和安装的软件生成 Visual Studio 项目文件。

#### 2、编译项目

在生成项目文件后，找到UE5.sln文件，使用 Visual Studio 打开它。

在 Visual Studio 中，选择 “Debug” 或 “Release” 配置（通常在生成游戏时使用 “Release” 配置）。

右键单击解决方案资源管理器中的 “UE5” 项目，然后选择 “生成”。编译过程可能会花费很长时间，因为 Unreal Engine 代码量庞大。

![](https://github.com/HushengStudent/myUnreal/blob/main/Doc/Basics/build_engine/vs_install1.png?raw=true)
![](https://github.com/HushengStudent/myUnreal/blob/main/Doc/Basics/build_engine/vs_install2.png?raw=true)

对于 Unreal 5.4.4 在 Windows平台编译，通常可以使用 Windows SDK 10.0.19041.0 或更高版本。这是因为 Unreal Engine 5 有一定的 Windows API 依赖，并且随着引擎的更新，对较新的 SDK 功能也有更好的支持。
