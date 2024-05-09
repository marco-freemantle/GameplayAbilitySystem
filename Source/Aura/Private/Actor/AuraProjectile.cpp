// Copyright Marco Freemantle


#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Character/AuraCharacter.h"
#include "Player/AuraPlayerState.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 1250.f;
	ProjectileMovement->MaxSpeed = 1250.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::Destroyed()
{
	if(!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	}
	Super::Destroyed();
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	UGameplayStatics::SpawnSoundAttached(InAirSound, GetRootComponent(), EName::None, 
	FVector(ForceInit), 
	FRotator::ZeroRotator, 
	EAttachLocation::KeepRelativeOffset, 
	true );
	SetLifeSpan(LifeSpan);
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(CheckHitSelf(OtherActor)) return;
	
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());

	if(HasAuthority())
	{
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

bool AAuraProjectile::CheckHitSelf(AActor* OtherActor) const
{
	AAuraCharacter* CharacterHit = Cast<AAuraCharacter>(OtherActor);
	if (CharacterHit == nullptr) return false;
	
	AAuraPlayerState* HitPlayerState = Cast<AAuraPlayerState>(CharacterHit->GetPlayerState());
	if (HitPlayerState == nullptr) return false;
	
	AAuraPlayerState* InstigatorPlayerState = Cast<AAuraPlayerState>(GetOwner());
	if (InstigatorPlayerState == nullptr) return false;
	
	if (HitPlayerState == InstigatorPlayerState) return true;
    
	return false;
}


