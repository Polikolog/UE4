// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometry.generated.h"



UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};



USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 10.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 2.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;
};



UCLASS()
class SANDBOX_API ABaseGeometry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometry();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Geometry Data")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere , Category = "Weapon")
	int32 WeaponNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Health = 35.242453;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	bool IsDead = false;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int32 KillsNum = 7;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector InitialLocation;

	void printTypes();
	void printTransform();
	void HandleMovement();

};
