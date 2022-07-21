// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	DoActorSpawn2();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHubActor::DoActorSpawn()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) { return; }
	for (size_t i = 0; i < 10; ++i)
	{
		const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.f, 300.f * i, 300.f));
		ABaseGeometry* BaseGeometry = World->SpawnActor<ABaseGeometry>(GeometryClass, GeometryTransform);
		if (!ensure(BaseGeometry)) { return; }

		FGeometryData Data;
		Data.MoveType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
		BaseGeometry->SetGeometryData(Data);
	}
}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) { return; }
	for (size_t i = 0; i < 10; ++i)
	{
		const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.f, 300.f * i, 700.f));
		ABaseGeometry* BaseGeometry = World->SpawnActorDeferred<ABaseGeometry>(GeometryClass, GeometryTransform);
		if (!ensure(BaseGeometry)) { return; }

		FGeometryData Data;
		Data.Color = FLinearColor::MakeRandomColor();
		Data.MoveType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
		BaseGeometry->SetGeometryData(Data);
		BaseGeometry->FinishSpawning(GeometryTransform);
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) { return; }
	for (const auto Payload : GeometryPayloads)
	{
		ABaseGeometry* BaseGeometry = World->SpawnActorDeferred<ABaseGeometry>(Payload.GeometryClass, Payload.InitialTransform);
		if (!ensure(BaseGeometry)) { return; }

		BaseGeometry->SetGeometryData(Payload.GeometryData);
		BaseGeometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
		BaseGeometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
		BaseGeometry->FinishSpawning(Payload.InitialTransform);
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s - have color %s"), *Name, *Color.ToString())
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!ensure(Actor)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s - time out"), *Actor->GetName())

	auto BaseGeometry = Cast<ABaseGeometry>(Actor);
	if (!ensure(BaseGeometry)) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Actor: %s :::: %s"), *Actor->GetName(), *BaseGeometry->GetGeometryData().ToString())

	BaseGeometry->Destroy();
}

