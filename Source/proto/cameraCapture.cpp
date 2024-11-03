// Fill out your copyright notice in the Description page of Project Settings.


#include "cameraCapture.h"

// Sets default values
AcameraCapture::AcameraCapture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AcameraCapture::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AcameraCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // ������ �����忡�� UpdateCameraTexture�� �����ϵ��� ť�� �߰��մϴ�.
    ENQUEUE_RENDER_COMMAND(UpdateCameraTextureCommand)(
        [this](FRHICommandListImmediate& RHICmdList)
        {
            UpdateCameraTexture();
        });

}

void AcameraCapture::UpdateCameraTexture()
{
    UARTexture* NewCameraTexture = UARBlueprintLibrary::GetARTexture(EARTextureType::CameraImage);
    if (!NewCameraTexture) {
        UE_LOG(LogTemp, Warning, TEXT("CameraTexture or Resource is null"));
        return;
    }
    UARTextureCameraImage* CameraImage = Cast<UARTextureCameraImage>(NewCameraTexture);
    if (!NewCameraTexture || !NewCameraTexture->Resource)
    {
        UE_LOG(LogTemp, Warning, TEXT("CameraImage or Resource is null"));
        return;
    }

    // 2. �ؽ�ó ������ ���
    FTexture2DRHIRef Texture2D = NewCameraTexture->GetResource()->GetTexture2DRHI();
    int32 Width = NewCameraTexture->GetSurfaceWidth();
    int32 Height = NewCameraTexture->GetSurfaceHeight();
    uint32 Stride;

    UE_LOG(LogTemp, Display, TEXT("width: %d, heigth: %d"), Width, Height);

    // �ȼ� �����͸� ��װ� ���ɴϴ�
    uint8* PixelData = static_cast<uint8*>(RHILockTexture2D(Texture2D, 0, RLM_ReadOnly, Stride, false));
    if (!PixelData)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to lock texture data"));
        return;
    }

    // 6. �ؽ�ó ���
    RHIUnlockTexture2D(Texture2D, 0, false);

    // ���� ProcessedMat�� ����Ͽ� ���ϴ� �۾��� ������ �� �ֽ��ϴ�.
}

