// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseGeometry.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"



USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometry> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};



UCLASS()
class SANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometry> GeometryClass;

	/*UPROPERTY(EditAnywhere)
	UClass* Class;

	UPROPERTY(EditAnywhere)
	ABaseGeometry* GeometryObject;*/

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void DoActorSpawn();
	void DoActorSpawn1();
	void DoActorSpawn2();

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	void OnTimerFinished(AActor* Actor);

};
