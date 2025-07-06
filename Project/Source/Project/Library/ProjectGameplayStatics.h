// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Project/Project.h"
#include "Project/GamePlay/Character/ProjectCharacter.h"
#include "Project/GamePlay/GameMode/ProjectGameMode.h"
#include "Project/GamePlay/GameStateBase/ProjectGameStateBase.h"
#include "Project/GamePlay/PlayerController/ProjectPlayerController.h"
#include "Project/GamePlay/PlayerState/ProjectPlayerState.h"
#include "ProjectGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

	/**
	 * ProjectGameState,可能没有
	 */
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<AProjectGameStateBase, T>>>
	static T* GetProjectGameState(const UObject* WorldContextObject);

	/**
	 * ProjectGameMode,只有服务器有
	 */
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<AProjectGameMode, T>>>
	static T* GetProjectGameMode(const UObject* WorldContextObject);

	/**
	 * ProjectPlayerController,一定有
	 */
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<AProjectPlayerController, T>>>
	static T* GetFirstProjectPlayerController(const UObject* WorldContextObject);

	/**
	 * ProjectPlayerState,可能没有
	 */
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<AProjectPlayerState, T>>>
	static T* GetFirstProjectPlayerState(const UObject* WorldContextObject);

	/**
	 * ProjectCharacter,可能没有
	 */
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<AProjectCharacter, T>>>
	static T* GetFirstProjectCharacter(const UObject* WorldContextObject);
	
public:
	UFUNCTION(BlueprintCallable, Category = "ProjectGameplayStatics")
	static AProjectGameStateBase* GetProjectGameState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ProjectGameplayStatics")
	static AProjectGameMode* GetProjectGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ProjectGameplayStatics")
	static AProjectPlayerController* GetFirstProjectPlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ProjectGameplayStatics")
	static AProjectPlayerState* GetFirstProjectPlayerState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ProjectGameplayStatics")
	static AProjectCharacter* GetFirstProjectCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "ProjectGameplayStatics")
	static FVector2D GetMouseScreenPosition(const UObject* WorldContextObject);
};

template <typename T, typename>
T* UProjectGameplayStatics::GetProjectGameState(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(World));
	AGameStateBase* GameState = World->GetGameState();
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(GameState));
	return Cast<T>(GameState);
}

template <typename T, typename>
T* UProjectGameplayStatics::GetProjectGameMode(const UObject* WorldContextObject)
{
	AGameModeBase* GameModeBase = GetGameMode(WorldContextObject);
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(GameModeBase));
	return Cast<T>(GameModeBase);
}

template <typename T, typename>
T* UProjectGameplayStatics::GetFirstProjectPlayerController(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(World));
	APlayerController* PlayerController = World->GetFirstPlayerController();
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(PlayerController));
	return Cast<T>(PlayerController);
}

template <typename T, typename>
T* UProjectGameplayStatics::GetFirstProjectPlayerState(const UObject* WorldContextObject)
{
	const AProjectPlayerController* FirstProjectPlayerController = GetFirstProjectPlayerController(WorldContextObject);
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(FirstProjectPlayerController));
	APlayerState* PlayerState = FirstProjectPlayerController->PlayerState;
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(PlayerState));
	return Cast<T>(PlayerState);
}

template <typename T, typename>
T* UProjectGameplayStatics::GetFirstProjectCharacter(const UObject* WorldContextObject)
{
	const AProjectPlayerController* FirstProjectPlayerController = GetFirstProjectPlayerController(WorldContextObject);
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(FirstProjectPlayerController));
	ACharacter* Character = FirstProjectPlayerController->GetCharacter();
	CHECK_CONDITION_OR_RETURN_NULLPTR(IsValid(Character));
	return Cast<T>(Character);
}

