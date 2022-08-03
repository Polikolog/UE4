// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUBaseProjectile;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUPGAME_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<ASTUBaseProjectile> ProjectileClass;

	virtual void MakeShot() override;

};
