#pragma once

#include "MassSpringNetwork.h"
#include "RuntimeMeshObjectBase.h"
#include "ClothActor.generated.h"

class MassSpringNetwork;

UCLASS()
class RMC_EXAMPLES_API AClothActor : public ARuntimeMeshObjectBase
{
    GENERATED_BODY()

private:
    bool bGenerated;

    float AnimationOffsetX = 0.0f;
    float AnimationOffsetY = 0.0f;

    int32 HalfWidth = 400;

    int32 Width = 30;
    int32 Depth = 60;

    float CellSize = 5;
    float Height = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Bounding Box")
        FBox BoundingBox;

    MassSpringNetwork Network;

public:
    // Sets default values for this actor's properties
    AClothActor();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    void Generate();
};
