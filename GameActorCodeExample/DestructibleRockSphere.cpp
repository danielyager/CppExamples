#include "DestructibleRockSphere.h"

/*
=========================================================================
Constructor - Sets default values and creates/attaches actor components.
=========================================================================
*/
ADestructibleRockSphere::ADestructibleRockSphere() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_DestructibleRockSphere"));
	Mesh->SetupAttachment(Root);

	DissolveVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraVFX"));
	DissolveVFX->SetupAttachment(Root);
}

/*
=============================================
Called when the game starts or when spawned.
=============================================
*/
void ADestructibleRockSphere::BeginPlay() {
	Super::BeginPlay();
	bCanTriggerDestroy = true;
}

/*
=======================================================================
"Destroys" the rock actor, removing all collision and visibility of the
object. Keeps the actor alive in memory though for quick and easy
respawning.
=======================================================================
*/
void ADestructibleRockSphere::DestroyRock() {
	if (DissolveVFX && Mesh) {
		DissolveVFX->SetWorldLocation(Mesh->GetComponentLocation());
		DissolveVFX->Activate();
		Mesh->SetVisibility(false);
		SetActorEnableCollision(false);
	}
}

/*
=======================================================================
Handles logic for overlap events with this actor. Checks to see what's
overlapping with it and reacts accordingly.
=======================================================================
*/
void ADestructibleRockSphere::HandleOverlap( AActor* Other ) {
	if ((Cast<ADestructibleRockSphere>(Other))) {
		return;
	}

	if (ABasicPlayerProjectile* projectile = Cast<ABasicPlayerProjectile>(Other)) {
		if (Manager && bCanTriggerDestroy) {
			SimulatePhysics(true);
			Manager->DestroyRocksWithDelay(projectile->GetActorLocation());
		}
	}
}

/*
=======================================================================
Adds an impulse force to the rock. Takes in an impulse location and
intensity as parameters. The direction of impulse force on the rock is
calculated from the location of the force relative to the rock actor.
=======================================================================
*/
void ADestructibleRockSphere::AddBlastForceAtLocation( const FVector& impulseLocation, const float impulseintensity ) {
	if (!Mesh) {
		return;
	}

	FVector impulseForce = Mesh->GetComponentLocation() - impulseLocation;
	impulseForce.Normalize();
	Mesh->AddImpulseAtLocation(impulseForce * impulseintensity, impulseLocation);
}

/*
=======================================================================
Respawns the rock actor by adding all collision, removing physics, and
adding visibility of the object, along with sending it back to its
original location.
=======================================================================
*/
void ADestructibleRockSphere::RespawnRock() {
	if (!Mesh) {
		return;
	}

	Mesh->SetAllPhysicsPosition(GetActorLocation());
	Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	DissolveVFX->SetWorldLocation(Mesh->GetComponentLocation());
	SimulatePhysics(false);
	Mesh->SetVisibility(true);
	SetActorEnableCollision(true);
	bCanTriggerDestroy = true;
}

/*
======================================================
Returns the magnitude of the actor's velocity vector.
======================================================
*/
float ADestructibleRockSphere::GetRockVelocityIntensity() {
	if (Mesh) {
		return Mesh->GetPhysicsLinearVelocity().Length();
	}
	return 0.0f;
}

/*
======================================
Returns the actor's velocity vector.
======================================
*/
FVector ADestructibleRockSphere::GetRockVelocity() {
	if (Mesh) {
		return Mesh->GetPhysicsLinearVelocity();
	}
	return FVector::ZeroVector;
}

/*
=========================================================
Sets whether or not physics is turned on for this actor,
allowing control of physics use outside of this class.
=========================================================
*/
void ADestructibleRockSphere::SimulatePhysics( const bool simulatePhysics ) {
	if (Mesh) {
		Mesh->SetSimulatePhysics(simulatePhysics);
	}
}

/*
===================================
GETTER/SETTER methods for fields.
===================================
*/

void ADestructibleRockSphere::SetManager( const ADestructibleObjectsManager* newManager ) {
	Manager = newManager;
}

void ADestructibleRockSphere::SetCanTriggerDestroy( const bool canTriggerDestroy ) {
	bCanTriggerDestroy = canTriggerDestroy;
}

bool ADestructibleRockSphere::GetCanTriggerDestroy() {
	return bCanTriggerDestroy;
}