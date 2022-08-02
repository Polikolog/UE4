// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUBaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh Componet");
    SetRootComponent(SkeletalMeshComponent);

}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    check(SkeletalMeshComponent)
}

void ASTUBaseWeapon::MakeShot() 
{
    if (!ensure(GetWorld()))
        return;

    FVector TraceStart, TraceEnd;
    if(!GetTraceData(TraceStart, TraceEnd))
        return;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 20, FColor::Red, false, 3.f, 0, 3.0f);
        
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}

void ASTUBaseWeapon::Fire() 
{
    MakeShot();
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const 
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;              // GetMuzzleWorldLocation();
    //const FVector ShootDirection = ViewRotation.Vector(); // SocketTransform.GetRotation().GetForwardVector();
    TraceEnd = TraceStart + ViewRotation.Vector() * TraceMaxDistance;
    return true;
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!ensure(Player))
        return nullptr;

    const auto Controller = Player->GetController<APlayerController>();
    if (!ensure(Controller))
        return nullptr;
    return Controller;
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!ensure(Controller))
        return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const 
{
    return SkeletalMeshComponent->GetSocketLocation(MuzzleSocketName);
}

void ASTUBaseWeapon::MakeDamage(const FHitResult& HitResult) 
{
    const auto DamageActor = HitResult.GetActor();

    /*if (!HitResult.GetActor()->IsA<ACharacter>())
        return;*/
    HitResult.GetActor()->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
