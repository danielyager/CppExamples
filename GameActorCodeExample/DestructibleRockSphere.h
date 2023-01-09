#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleRockSphere.generated.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "DestructibleObjectsManager.h"
#include "BasicPlayerProjectile.h"

UCLASS()
class MAGESOCIETY_API ADestructibleRockSphere : public AActor {
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* DissolveVFX;

	UPROPERTY()
	ADestructibleObjectsManager* Manager;

	UPROPERTY()
	bool bCanTriggerDestroy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ADestructibleRockSphere();

	void SetManager(ADestructibleObjectsManager* newManager);

	void AddBlastForceAtLocation( const FVector& impulseLocation, const float impulseIntensity );

	UFUNCTION(BlueprintCallable)
	void SimulatePhysics( const bool simulatePhysics );

	UFUNCTION(BlueprintCallable)
	void RespawnRock();

	UFUNCTION(BlueprintCallable)
	void SetCanTriggerDestroy( const bool canTriggerDestroy );

	UFUNCTION(BlueprintCallable)
	bool GetCanTriggerDestroy();

	UFUNCTION(BlueprintCallable)
	void DestroyRock();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DestroyRockWithDelay( const float delayTime );

	UFUNCTION(BlueprintCallable)
	void HandleOverlap( AActor* Other );

	UFUNCTION(BlueprintCallable)
	float GetRockVelocityIntensity();

	UFUNCTION(BlueprintCallable)
	FVector GetRockVelocity();
};
