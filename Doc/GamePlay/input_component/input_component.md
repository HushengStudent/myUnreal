APawn接口调用设置输入

```C++
// APawn interface
virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
```

#### UInputAction（输入动作）

1、代表一个抽象的输入动作（如 "跳跃"、"开火"、"移动"），而非具体的按键映射

2、可以定义输入值的类型（布尔值、浮点值、2D 向量等），适用于不同类型的输入（按键、摇杆、鼠标等）

3、允许设置触发规则（如按下、释放、值变化等）

4、是输入处理的核心，游戏逻辑通过监听 InputAction 来响应输入

#### UInputMappingContext（输入映射上下文）

1、管理一组 InputAction 与具体输入设备的映射关系

2、可以在不同游戏状态下激活 / 禁用整个映射上下文（如菜单状态和游戏状态使用不同的映射）

3、支持映射优先级，便于处理复杂的输入冲突场景

4、允许为同一 InputAction 设置多个输入触发方式（如键盘和手柄都可控制移动）

#### UEnhancedInputLocalPlayerSubsystem（增强化输入本地玩家子系统）

1、是 Enhanced Input 系统的核心管理器，每个 LocalPlayer 对应一个实例

2、负责管理 InputMappingContext 的激活和优先级

3、提供接口来添加 / 移除映射上下文，控制输入的激活状态

4、作为输入系统与玩家控制器之间的桥梁

#### UEnhancedInputComponent（增强输入组件）

1、继承自 UInputComponent，用于绑定 InputAction 到具体的回调函数

2、提供更灵活的绑定方式，支持不同的输入事件类型（如开始、结束、值变化）

3、可以直接在蓝图或 C++ 中绑定输入动作的响应函数

4、支持为绑定设置修饰符和触发器，实现复杂的输入逻辑

```C++
// Input

void AProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
```

![](https://github.com/HushengStudent/myUnreal/blob/main/Doc/GamePlay/input_component/input_component.png?raw=true)