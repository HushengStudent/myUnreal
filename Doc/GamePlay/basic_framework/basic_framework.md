![](https://github.com/HushengStudent/myUnreal/blob/main/Doc/GamePlay/basic_framework/gameplay1.png?raw=true)

UEngine：

UObject：UObject提供供UE运行的最基本的功能：垃圾收集、引用自动更新、反射、序列化、自动检测默认变量的更改、自动变量初始化、和虚幻引擎编辑器的自动交互、运行时类型识别、网络复制；

AActor：UObject子类：网络复制、动态创建、每帧运行；

APlayerStart：

APawn：AActor子类：被Controller控制、物理碰撞、MovementInput；

ACharacter：ACharacter是一个专门为人形角色定制的APawn，自带CharacterMovement组件；

ASpectatorPawn：观战玩家；

AController：控制APawn运动；

APlayerController：相机管理、输入响应、UPlayer关联、HUD、音源监听；

AAIController：自动寻路、AI Component、Task；

AInfo：数据保存类的基类；

AWordSettings：AInfo子类：用来配置和保存一些Level配置；

AGameMode：记录GameMode中各种类的信息、创建Pawn和PlayerController等；

AGameState：游戏状态；

APlayerState：玩家状态；

UActorComponent：

USceneComponent：USceneComponent主要提供两大能力，一是Transform，二是SceneComponent的互相嵌套；

UPrimitiveComponent：主要提供Actor用于物体渲染和碰撞相关的基础能力；

UMeshComponent：

UChildActorComponent：

UWorld：

FWorldContext：引擎UWorld上下文的类；

UGameInstance：

UNetDriver：处理网络同步；

UNetConnection：处理其他玩家在本地客户端中的APawn的类；
