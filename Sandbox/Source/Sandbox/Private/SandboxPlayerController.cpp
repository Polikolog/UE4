// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);

}

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);

}

void ASandboxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) { return; }

	auto CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	if (!ensure(CurrentPawn)) return;
	Possess(CurrentPawn);
	UE_LOG(LogSandboxPlayerController, Warning, TEXT("U change pawn: %d"), CurrentPawnIndex);
}
