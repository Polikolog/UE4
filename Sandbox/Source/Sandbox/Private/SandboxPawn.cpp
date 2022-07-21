// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h" 
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	StaticMeshComponent->SetupAttachment(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(GetRootComponent());
}

void ASandboxPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ASandboxPawn::UnPossessed()
{
	Super::UnPossessed();


}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!VelocityVector.IsZero()) 
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
		VelocityVector = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASandboxPawn::MoveRight);
}

void ASandboxPawn::MoveForward(float Amount)
{
	UE_LOG(LogSandboxPawn, Warning, TEXT("Amount: %f"), Amount)
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	UE_LOG(LogSandboxPawn, Warning, TEXT("Amount: %f"), Amount)
	VelocityVector.Y = Amount;
}

