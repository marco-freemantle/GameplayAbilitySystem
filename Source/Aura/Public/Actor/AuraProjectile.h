// Copyright Marco Freemantle

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool CheckHitSelf(AActor* OtherActor) const;
	
	bool bHit = false;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> InAirSound;
};
