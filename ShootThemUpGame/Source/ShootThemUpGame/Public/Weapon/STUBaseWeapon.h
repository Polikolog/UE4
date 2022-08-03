// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTTHEMUPGAME_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void StartFire();

    virtual void StopFire();

	virtual bool GetTraceData(FVector& TraceStrat, FVector& TraceEnd) const;

    APlayerController* GetPlayerController() const;

    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

    FVector GetMuzzleWorldLocation() const;

private:
    

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    FName MuzzleSocketName = "MuzzleFlashSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TraceMaxDistance = 1500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
	float DamageAmount = 10.0f;

	void MakeDamage(const FHitResult& HitResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	 virtual void MakeShot();

};
