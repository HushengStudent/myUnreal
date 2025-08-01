// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerController.h"

#include "Project/Cheat/ProjectCheatManager.h"

AProjectPlayerController::AProjectPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

AProjectPlayerState* AProjectPlayerController::GetProjectPlayerState() const
{
	return CastChecked<AProjectPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UProjectAbilitySystemComponent* AProjectPlayerController::GetProjectAbilitySystemComponent() const
{
	const AProjectPlayerState* ProjectPlayerState = GetProjectPlayerState();
	return (ProjectPlayerState ? ProjectPlayerState->GetProjectAbilitySystemComponent() : nullptr);
}

bool AProjectPlayerController::TryToRecordClientReplay()
{
	//TODO
	return false;
}

bool AProjectPlayerController::ShouldRecordClientReplay()
{
	//TODO
	return false;
}

void AProjectPlayerController::ServerCheatAll_Implementation(const FString& Msg)
{
}

bool AProjectPlayerController::ServerCheatAll_Validate(const FString& Msg)
{
	//TODO
	return true;
}

void AProjectPlayerController::ServerCheat_Implementation(const FString& Msg)
{
}

bool AProjectPlayerController::ServerCheat_Validate(const FString& Msg)
{
	//TODO
	return true;
}

void AProjectPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	CheatClass = UProjectCheatManager::StaticClass();
	
#if !UE_BUILD_SHIPPING
	EnableCheats();
#endif
	
}

void AProjectPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AProjectPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AProjectPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AProjectPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AProjectPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
}

void AProjectPlayerController::CleanupPlayerState()
{
	Super::CleanupPlayerState();
}

void AProjectPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AProjectPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
}

void AProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AProjectPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);
}

void AProjectPlayerController::AddCheats(bool bForce)
{
	Super::AddCheats(bForce);
}

void AProjectPlayerController::UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId)
{
	Super::UpdateForceFeedback(InputInterface, ControllerId);
}

void AProjectPlayerController::UpdateHiddenComponents(const FVector& ViewLocation,
	TSet<FPrimitiveComponentId>& OutHiddenComponents)
{
	Super::UpdateHiddenComponents(ViewLocation, OutHiddenComponents);
}

void AProjectPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PreProcessInput(DeltaTime, bGamePaused);
}

void AProjectPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
}
