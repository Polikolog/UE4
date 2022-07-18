// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometry.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxGeometry, All, All)

// Sets default values
ABaseGeometry::ABaseGeometry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometry::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();

}

// Called every frame
void ABaseGeometry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();

}

void ABaseGeometry::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
		case EMovementType::Sin:
		{
			FVector CurrentLocation = GetActorLocation();
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			SetActorLocation(CurrentLocation);
		}
		case EMovementType::Static:
		{
			break;
		}
		default: break;
	}
}

void ABaseGeometry::printTypes()
{
	UE_LOG(LogSandboxGeometry, Display, TEXT("Hello Unreal Engine!"))


	FString WeaponsNumStr = "Weapon num = " + FString::FromInt(WeaponNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is Dead = " + FString(IsDead ? "true" : "false");

	UE_LOG(LogSandboxGeometry, Log, TEXT("%s"), *WeaponsNumStr)
	UE_LOG(LogSandboxGeometry, Log, TEXT("%s"), *HealthStr)
	UE_LOG(LogSandboxGeometry, Log, TEXT("%s"), *IsDeadStr)

	FString Stat = FString::Printf(TEXT(" \n\t == All Stat == \n\t %s \n\t %s \n\t %s"), 
		*WeaponsNumStr, 
		*HealthStr, 
		*IsDeadStr);

	UE_LOG(LogSandboxGeometry, Log, TEXT("%s"), *Stat)

	GEngine->AddOnScreenDebugMessage(-1, 
		3.f,
		FColor::Green,
		Stat,
		false,
		FVector2D(0.9f, 0.9f));
}

void ABaseGeometry::printTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FQuat Quaternion = Transform.GetRotation();
	FRotator Rotation = Quaternion.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogSandboxGeometry, Display, TEXT("Hello Unreal Engine!"))
	UE_LOG(LogSandboxGeometry, Display, TEXT("Transform: %s"), *Transform.ToString())
	UE_LOG(LogSandboxGeometry, Display, TEXT("Location: %s"), *Location.ToString())
	UE_LOG(LogSandboxGeometry, Display, TEXT("Quaternion: %s"), *Quaternion.ToString())
	UE_LOG(LogSandboxGeometry, Display, TEXT("Rotation: %s"), *Rotation.ToString())
	UE_LOG(LogSandboxGeometry, Display, TEXT("Scale: %s"), *Scale.ToString())

	UE_LOG(LogSandboxGeometry, Warning, TEXT("Human Transform: %s"),
		*Transform.ToHumanReadableString())

}
