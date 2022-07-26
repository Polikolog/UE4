// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUPGAME_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	UPROPERTY(VisibleAnywhere, Category = "Component")
    USceneComponent* SceneComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Geometry")
	float Radius = 500.f;

	UPROPERTY(EditAnywhere, Category = "Geometry")
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, Category = "Damage")
    float Damage = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Damage")
    bool DoFullDamage = true;

	UPROPERTY(EditAnywhere, Category = "Damage")
    TSubclassOf<UDamageType> DamageType;

  public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
