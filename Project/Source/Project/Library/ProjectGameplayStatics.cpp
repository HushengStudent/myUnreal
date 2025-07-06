// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameplayStatics.h"

AProjectGameStateBase* UProjectGameplayStatics::GetProjectGameState(const UObject* WorldContextObject)
{
	return GetProjectGameState<AProjectGameStateBase>(WorldContextObject);
}

AProjectGameMode* UProjectGameplayStatics::GetProjectGameMode(const UObject* WorldContextObject)
{
	return GetProjectGameMode<AProjectGameMode>(WorldContextObject);
}

AProjectPlayerController* UProjectGameplayStatics::GetFirstProjectPlayerController(const UObject* WorldContextObject)
{
	return GetFirstProjectPlayerController<AProjectPlayerController>(WorldContextObject);
}

AProjectPlayerState* UProjectGameplayStatics::GetFirstProjectPlayerState(const UObject* WorldContextObject)
{
	return GetFirstProjectPlayerState<AProjectPlayerState>(WorldContextObject);
}

AProjectCharacter* UProjectGameplayStatics::GetFirstProjectCharacter(const UObject* WorldContextObject)
{
	return GetFirstProjectCharacter<AProjectCharacter>(WorldContextObject);
}

FVector2D UProjectGameplayStatics::GetMouseScreenPosition(const UObject* WorldContextObject)
{
	const AProjectPlayerController* PC = GetFirstProjectPlayerController(WorldContextObject);
	if (!PC)
	{
		return FVector2D::Zero();
	}
	float MouseX, MouseY;
	PC->GetMousePosition(MouseX, MouseY); // 左下角为原点
	return FVector2D(MouseX, MouseY);
}
