
开始工程后切换地图到L_ShooterGym

设置：

编辑器设置，取消Allow Player Bots to Attack

项目设置里默认GameMode已经设置为ALyraGameMode

WorldSettings设置GameplayExperience

流程：

```C++
ALyraGameMode::InitGame

ALyraGameMode::HandleMatchAssignmentIfNotExpectingOne

ALyraGameMode::OnMatchAssignmentGiven

ULyraExperienceManagerComponent::SetCurrentExperience

ULyraExperienceManagerComponent::StartExperienceLoad

ULyraExperienceManagerComponent::OnExperienceLoadComplete

	ULyraExperienceManagerComponent::OnGameFeaturePluginLoadComplete

	ULyraExperienceManagerComponent::OnExperienceFullLoadCompleted

		CollectGameFeaturePluginURLs
	
ALyraPlayerState::OnExperienceLoaded

	GetPawnDataForController
	
ActivateListOfActions
```