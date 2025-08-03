## UCameraComponent

### UCameraComponent：相机渲染

负责渲染玩家看到的画面，直接决定视角、视野范围（FOV）、近 / 远裁剪平面等渲染参数

1、Field of View（FOV）：视野角度，值越大画面越广角。

2、Aspect Ratio：宽高比，通常与屏幕分辨率匹配。

3、Near Clip Plane / Far Clip Plane：近 / 远裁剪面，控制相机能看到的最近和最远距离。

4、Projection Mode：投影模式（透视投影 / 正交投影），3D 游戏通常用透视投影模拟真实视角。

单独使用时，相机位置 / 旋转完全依赖其父组件，无法自动处理碰撞或平滑跟随逻辑。

### USpringArmComponent：弹簧臂

一端固定在父组件（如角色）上，另一端挂载相机，通过物理模拟般的逻辑自动调整相机位置，核心作用是避免相机穿模和实现平滑跟随。

1、Target Arm Length：弹簧臂的理想长度（相机到父组件的默认距离）。

2、Socket Offset：弹簧臂末端（相机挂载点）相对臂本身的偏移量。

3、Relative Rotation：弹簧臂相对父组件的旋转角度（决定相机初始朝向）。

4、碰撞检测：开启 Do Collision Test 后，弹簧臂会检测路径上的障碍物（如墙壁），自动缩短长度让相机避开障碍物，避免穿模。

5、平滑旋转：通过 Probe Size（碰撞检测球体大小）、Collision Response（碰撞响应规则）等参数控制碰撞时的行为。

6、滞后效果：Lag Speed（位置滞后）和 Rotation Lag Speed（旋转滞后）参数可实现相机跟随的延迟效果，让视角变化更平滑（如角色快速转向时，相机缓慢跟上，避免画面抖动）。

### APlayerCameraManager：相机管理器

1、全局相机行为控制

2、处理相机抖动(Camera Shake)

3、视角过渡(如死亡镜头切换)

4、后期处理特效管理

### 实现：
```language
角色组件（Character）
└── USpringArmComponent（作为角色的子组件）
    └── UCameraComponent（作为弹簧臂的子组件）
```

1、角色移动 / 旋转时，弹簧臂跟随角色运动，并根据自身属性（长度、旋转）计算理想的相机位置。

2、弹簧臂检测到障碍物时，自动调整长度（缩短），将相机 “推” 到无遮挡的位置。

3、相机最终位置由弹簧臂的调整结果决定，渲染出对应的视角。

优势：通过弹簧臂的中间层处理，相机既能跟随角色，又能智能避开障碍物，同时保持平滑的视觉过渡。
```C++
/** Camera boom positioning the camera behind the character */
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
USpringArmComponent* SpringArm;

/** Follow camera */
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
UCameraComponent* FollowCamera;
```


```C++
// Create a camera boom (pulls in towards the player if there is a collision)
SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
SpringArm->SetupAttachment(RootComponent);
SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

// Create a follow camera
FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

```

### 视角控制
```C++
// 在角色中实现输入
void AProjectCharacter::SetupPlayerInputComponent(UInputComponent* Input) {
    Input->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    Input->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

// 旋转限制 (防止脖子翻转)
void AProjectCharacter::AddControllerPitchInput(float Val) {
    const float ClampedPitch = FMath::Clamp(GetControlRotation().Pitch + Val, -89.f, 89.f);
    GetController()->SetControlRotation(FRotator(ClampedPitch, GetControlRotation().Yaw, 0));
}
```

### 相机碰撞优化
```C++
# SpringArm设置
SpringArm->ProbeChannel = ECC_Camera;      // 专用碰撞通道
SpringArm->bDoCollisionTest = true;        // 启用碰撞检测
SpringArm->CameraCollisionRadius = 12.0f;  // 检测胶囊体半径
```

### 动态视角切换
```C++
// 切换到瞄准视角
void AProjectCharacter::EnterAimMode()
{
    if (SpringArm)
    {
        SpringArm->SetTargetArmLength(100.0f); // 缩短臂长
        SpringArm->SetRelativeRotation(FRotator(-5.0f, 0, 0)); // 略微调整角度
    }
    if (FollowCamera)
    {
        Camera->SetFieldOfView(60.0f); // 缩小视野，模拟瞄准镜
    }
}
```

### 相机抖动
```C++
// 实现相机抖动（如开枪时）
void AProjectCharacter::FireWeapon() {
    if (APlayerCameraManager* CamManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager) {
        CamManager->StartCameraShake(WeaponFireShake, 1.0f);
    }
}
```

### 动态修改FOV
```C++
// 动态修改FOV（奔跑时）
void AProjectCharacter::SprintStart() {
    Camera->SetFieldOfView(100.f); // 扩大视野
    SpringArm->CameraLagSpeed = 20.f; // 加快镜头跟随
}
```

### 死亡视角
```C++
// 死亡视角切换
void AProjectCharacter::OnDeath() {
    if (APlayerCameraManager* CamManager = ...) {
        CamManager->SetViewTargetWithBlend(DeathCameraActor, 1.5f); 
    }
}
```

### 头部晃动
```C++
// 在Tick中实现呼吸效果
void AProjectCharacter::Tick(float DeltaTime) {
    float BobAmount = FMath::Sin(GetWorld()->TimeSeconds * 2.5f) * 0.15f;
    SpringArm->SetRelativeLocation(FVector(0, 0, 70 + BobAmount)); 
}
```

### 穿墙处理
```C++
// 在SpringArm的OnCameraCollision中
if (BlockingHit.bBlockingHit && BlockingHit.Component->ComponentHasTag("Wall")) {
    // 透明化墙壁材质
    BlockingHit.Component->SetScalarParameterValue("Opacity", 0.3f);
}
```

### 常见问题
1、相机穿模：检查 Probe Size 是否过小（无法检测到细小型障碍物），或 Collision Response 是否未正确设置（如忽略了某些碰撞通道）。

2、相机跟随延迟过高：降低 Lag Speed（值越小响应越快），或在战斗等需要精准视角的场景中临时禁用滞后效果。

3、弹簧臂碰撞时视角突变：启用 Smooth Transition 让长度变化更平滑，或减小 Probe Size 使碰撞检测更精确（避免误判）。

### 调试技巧

控制台命令：

1、showdebug camera 显示相机参数

2、Camera.ToggleDebug 可视化碰撞检测

调试绘制：

SpringArm->bDrawDebug = true; // 显示碰撞胶囊
