// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARBlueprintLibrary.h"
#include "ARTextures.h"
#include "cameraCapture.generated.h"

UCLASS()
class PROTO_API AcameraCapture : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcameraCapture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateCameraTexture();

};
