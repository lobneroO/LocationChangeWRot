// Fill out your copyright notice in the Description page of Project Settings.

#include "RotationActor.h"
#include "Components/StaticMeshComponent.h" 
#include "Engine/StaticMesh.h"

// Sets default values
ARotationActor::ARotationActor() : AActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARotationActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> smcList;
	this->GetComponents<UStaticMeshComponent>(smcList, true);

	for (UStaticMeshComponent* comp : smcList)
	{
		if (comp->GetName().StartsWith("Rot_"))
		{
			RotatingComponents.Add(comp);
		}
	}
}

// Called every frame
void ARotationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//first randomly locate and rotate the actor
	FVector randomDeltaLoc(FMath::Rand() % 15, FMath::Rand() % 15, FMath::Rand() % 1);
	FVector randomDeltaRotAsVec(FMath::Rand() % 3, FMath::Rand() % 3, FMath::Rand() % 3);

	for (int32 i = 0; i < 3; i++)
	{
		if (FMath::Rand() % 2 == 0)
		{
			randomDeltaLoc[i] *= -1;
		}
		if (FMath::Rand() % 2 == 0)
		{
			randomDeltaRotAsVec[i] *= -1;
		}
	}
	FRotator randomDeltaRot(randomDeltaRotAsVec.X, randomDeltaRotAsVec.Y, randomDeltaRotAsVec.Z);

	FTransform trans = this->GetTransform();
	//trans.AddToTranslation(randomDeltaLoc);
	trans.SetRotation((trans.GetRotation().Rotator() + randomDeltaRot).Quaternion());

	this->SetActorTransform(trans);

	if (bRotateOnTick && RotatingComponents.Num() > 0)
	{
		FQuat deltaPitch(FVector(0, 1, 0), 0.5);
		
		for (UStaticMeshComponent* RotatingComponent : RotatingComponents)
		{
			RotatingComponent->AddLocalRotation(deltaPitch);
		}
	}
}

