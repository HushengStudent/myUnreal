#### 打开工程

下载引擎，编译

打开Project

工具，生成VisualStudio工程

#### 目录

Binaries：包含编译后的可执行文件、动态链接库等二进制文件。

DerivedDataCache：包含了引擎为提高性能而生成的派生数据，例如纹理的压缩版本、材质的预计算数据等。

Intermediate：包含了项目在编译和构建过程中生成的中间文件，例如编译后的目标文件、临时数据文件等。


Content（版本控制）：此文件夹包含了项目中的所有游戏内容，包括关卡、模型、材质、纹理、动画等资源。

Config（版本控制）：存放项目的配置文件，如项目设置、引擎配置、游戏模式设置等。

Plugins（版本控制）：如果项目使用了自定义插件或对引擎自带插件进行了修改，Plugins 文件夹需要进行版本控制。

Source（版本控制）：包含项目的 C++ 源代码。

Saved：

Config：存储项目特定的配置文件，这些文件记录了用户对项目的各种设置，例如自定义的输入映射、游戏模式的特殊配置等。
   
Logs：包含项目运行过程中产生的日志文件，这些日志记录了引擎和项目在运行时的各种信息，如错误信息、警告信息、系统状态等。
   
Maps：保存用户手动保存的关卡地图备份，这些备份是用户在开发过程中为了防止意外丢失而手动保存的关卡状态。
   
Screenshots：存放开发者在项目中截取的屏幕截图，这些截图可以用于记录项目的开发进度、展示效果或者进行问题反馈。
   
Collections：主要存放的是用户自定义的资源集合信息。
   
ShaderDebugInfo：包含着色器调试信息，这些信息是为了辅助开发者调试着色器代码而生成的。
   
SourceControl：主要存储与源代码管理系统交互过程中产生的临时数据和配置信息。
   
Telemetry：主要用于存储遥测数据。
   
UnrealBuildTool：Unreal Engine 的构建工具，用于编译项目代码、生成可执行文件和中间文件等。UnrealBuildTool文件夹包含了该构建工具的相关脚本、配置文件和可执行程序等。它是引擎自带的工具，其功能和代码由 Epic Games 维护和更新。
   
Autosaves：存放的是 Unreal Engine 自动保存的项目文件，比如关卡、蓝图等的临时副本。
   
AutoScreenshot.png 往往是引擎自动生成的截图。

.uproject（版本控制）：Unreal Engine 项目的核心配置文件，它定义了项目的基本属性和设置，包含了项目的名称、所使用的引擎版本、启用的插件列表、游戏模块信息等关键内容。这些设置决定了项目如何与 Unreal Engine 协同工作，以及项目的基本运行环境和功能特性。













