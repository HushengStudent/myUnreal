## UCharacterMovementComponent

### 一、基础

#### 移动模式（Movement Mode）

1、内置行走（Walking）、下落（Falling）、游泳（Swimming）、飞行（Flying）等模式，每种模式对应独立的Phys*函数（如PhysWalking处理地面移动）

2、模式切换触发物理重算（如行走时踏空自动切下落模式）


#### 加速度与速度计算

1、输入向量通过ScaleInputAcceleration()转换为加速度，受MaxAcceleration约束

2、速度更新公式：Velocity += Acceleration * DeltaTime，并受MaxWalkSpeed等参数限制

#### 碰撞与表面滑动

1、SafeMoveUpdatedComponent()移动碰撞体，若受阻则调用SlideAlongSurface()沿表面滑动

2、行走模式处理台阶（MaxStepHeight）和斜面摩擦（GroundFriction）

### 二、跳跃

跳跃通过修改垂直速度触发：

#### 输入触发

1、玩家输入调用Jump()，设置bPressedJump=true

2、CheckJumpInput()在每帧检测跳跃输入，若满足条件（如地面接触）则执行DoJump()

#### 速度突变

1、DoJump()直接将Velocity.Z设为JumpZVelocity（如1000单位/秒），无视当前加速度

2、空中控制通过AirControl参数调节横向移动能力

### 三、动画融合

动画与移动的同步依赖根骨骼运动（Root Motion）和网络平滑：

#### 根骨骼运动

1、动画蒙太奇可驱动位移（RootMotionSource），PerformMovement()优先采用其位移数据

2、非根骨骼运动时，动画蓝图读取Velocity和MovementMode更新状态机（如Idle/Run/Jump）

#### 网络平滑处理

模拟端（Simulated Proxy）通过SmoothCorrection()处理位置同步突变：

1、计算新旧位置偏差（MeshTranslationOffset），若超过MaxSmoothNetUpdateDist（默认256）则瞬移

2、SmoothClientPosition()每帧插值网格体位置，避免视觉卡顿

### 四、网络同步

1、（Autonomous Proxy）客户端预测移动，通过RPC发送ServerMove

2、（Authority）服务器校验移动，广播同步数据

3、（Simulated Proxy）直接应用服务器同步的ReplicatedMovement

![](https://github.com/HushengStudent/myUnreal/blob/main/Doc/GamePlay/\character_movement_component/\character_movement_component.png?raw=true)

#### 带宽优化

合并相似移动（如连续前进），通过ServerMoveDual发送多个移动批次

#### 纠偏（Reconciliation）

1、服务器发送ClientAdjustPosition包含正确位置/时间戳。

2、客户端回滚到该时间戳，重放SavedMoves队列中后续移动

#### 旋转同步

1、自治代理通过ServerMove发送控制器的ControlRotation。

2、服务器通过FaceRotation()应用旋转，受bUseControllerRotationYaw等参数约束

### 五、总结
#### 移动驱动

PerformMovement() → StartNewPhysics() → Phys*()

#### 网络同步

ReplicateMoveToServer()（自治代理） / OnRep_ReplicatedMovement()（模拟代理）

#### 纠偏

ClientAdjustPosition() → ClientUpdatePositionAfterServerUpdate()

#### UCharacterMovementComponent通过分层设计实现复杂移动逻辑

1、物理层：模式化处理移动物理（如重力、摩擦）。

2、网络层：自治代理预测-校验机制保障流畅性，模拟代理依赖服务器权威数据。

3、表现层：动画融合通过根骨骼运动与网络平滑衔接视觉与逻辑。

该设计在低延迟下提供流畅体验，高延迟时通过纠偏保障一致性，但需注意参数调优（如NetworkSmoothingMode）以平衡即时性与准确性