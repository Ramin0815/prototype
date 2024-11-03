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

    // 렌더링 스레드에서 UpdateCameraTexture를 실행하도록 큐에 추가합니다.
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

    // 2. 텍스처 데이터 잠금
    FTexture2DRHIRef Texture2D = NewCameraTexture->GetResource()->GetTexture2DRHI();
    int32 Width = NewCameraTexture->GetSurfaceWidth();
    int32 Height = NewCameraTexture->GetSurfaceHeight();
    uint32 Stride;

    UE_LOG(LogTemp, Display, TEXT("width: %d, heigth: %d"), Width, Height);

    // 픽셀 데이터를 잠그고 얻어옵니다
    uint8* PixelData = static_cast<uint8*>(RHILockTexture2D(Texture2D, 0, RLM_ReadOnly, Stride, false));
    if (!PixelData)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to lock texture data"));
        return;
    }

    // 6. 텍스처 언락
    RHIUnlockTexture2D(Texture2D, 0, false);

    // 이제 ProcessedMat을 사용하여 원하는 작업을 진행할 수 있습니다.
}

