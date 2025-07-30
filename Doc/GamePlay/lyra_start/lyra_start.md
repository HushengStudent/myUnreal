
开始工程后切换地图到L_ShooterGym

设置：

编辑器设置，取消Allow Player Bots to Attack

项目设置里默认GameMode已经设置为ALyraGameMode

WorldSettings设置GameplayExperience

流程：

```C++
//初始化GameMode
ALyraGameMode::InitGame

//初始化GameState
ALyraGameMode::InitGameState

ALyraGameMode::HandleMatchAssignmentIfNotExpectingOne

ALyraGameMode::OnMatchAssignmentGiven

//设置本次ExperienceId并加载
ULyraExperienceManagerComponent::SetCurrentExperience

ULyraExperienceManagerComponent::StartExperienceLoad

//Experience相关内容加载完成
ULyraExperienceManagerComponent::OnExperienceLoadComplete

//GameFeaturePlugin加载回调
ULyraExperienceManagerComponent::OnGameFeaturePluginLoadComplete

//GameFeaturePlugin加载完成
ULyraExperienceManagerComponent::OnExperienceFullLoadCompleted

ALyraGameMode::OnExperienceLoaded
	
	RestartPlayer
	
	ALyraGameState::AddPlayerState
	
	//角色初始化
	ALyraPlayerState::OnExperienceLoaded
	
		ALyraGameMode::GetPawnDataForController
		
		ALyraPlayerState::SetPawnData
		
		ULyraAbilitySet::GiveToAbilitySystem
	
//机器人
ULyraBotCreationComponent::OnExperienceLoaded

ULyraBotCreationComponent::SpawnOneBot
```