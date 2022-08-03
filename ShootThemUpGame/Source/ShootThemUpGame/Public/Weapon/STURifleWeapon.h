// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUPGAME_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;
	virtual void StopFire() override;

	virtual bool GetTraceData(FVector& TraceStrat, FVector& TraceEnd) const override;

 protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
	float BulletSpread = 1.5f;

	virtual void MakeShot() override;

private:
    FTimerHandle ShotTimerHandle;

};
