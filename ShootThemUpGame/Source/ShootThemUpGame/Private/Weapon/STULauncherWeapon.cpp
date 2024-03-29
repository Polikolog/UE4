// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUBaseProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    //

    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}