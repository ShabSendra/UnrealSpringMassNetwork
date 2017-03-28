// Copyright 2016 Chris Conway (Koderz). All Rights Reserved.

#include "RMC_Examples.h"
#include "ClothActor.h"
#include "RuntimeMeshLibrary.h"
#include "ParallelFor.h"

#include "Mass.h"

// Sets default values
AClothActor::AClothActor()// : Width(200), Height(200), CellSize(5.0f)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClothActor::BeginPlay()
{
    Super::BeginPlay();

    int32 XIndex;
    int32 YIndex;

    Mass mass;

    for(YIndex = 0; YIndex < Depth; YIndex++)
    {
        for(XIndex = 0; XIndex < Width; XIndex++)
        {
            mass.SetPosition(FVector(XIndex, YIndex, 0));
            mass.SetMass(0.3);
            Network.AddMass(mass);
        }
    }

    for(int i = 0; i < Width; ++i)
    {
        Network.GetMass(i).SetIsFixed(true);
    }

    Spring spring;

    // Structural springs along the X 
    for(YIndex = 0; YIndex < Depth; YIndex++)
    {
        for(XIndex = 0; XIndex < Width - 1; XIndex++)
        {
            spring.SetMasse1Id(YIndex * Width + XIndex);
            spring.SetMasse2Id(YIndex * Width + XIndex + 1);
            spring.SetStiffness(2000.0);
            spring.SetFreeLength(1.0);
            Network.AddSpring(spring);
        }
    }

    // Flexion springs along the X 
    for(YIndex = 0; YIndex < Depth; YIndex++)
    {
        for(XIndex = 0; XIndex < Width - 2; XIndex++)
        {
            spring.SetMasse1Id(YIndex * Width + XIndex);
            spring.SetMasse2Id(YIndex * Width + XIndex + 2);
            spring.SetStiffness(1.0);
            spring.SetFreeLength(2.0);
            Network.AddSpring(spring);
        }
    }

    // Structural springs along the Y 
    for(YIndex = 0; YIndex < Depth - 1; YIndex++)
    {
        for(XIndex = 0; XIndex < Width; XIndex++)
        {
            spring.SetMasse1Id(YIndex * Width + XIndex);
            spring.SetMasse2Id((YIndex + 1) * Width + XIndex);
            spring.SetStiffness(2000.0);
            spring.SetFreeLength(1.0);
            Network.AddSpring(spring);
        }
    }

    // Flexion springs along the Y
    for(YIndex = 0; YIndex < Depth - 2; YIndex++)
    {
        for(XIndex = 0; XIndex < Width; XIndex++)
        {
            spring.SetMasse1Id(YIndex * Width + XIndex);
            spring.SetMasse2Id((YIndex + 2) * Width + XIndex);
            spring.SetStiffness(1.0);
            spring.SetFreeLength(2.0);
            Network.AddSpring(spring);
        }
    }

    // Shear springs
    for(YIndex = 0; YIndex < Depth - 1; YIndex++)
    {
        for(XIndex = 0; XIndex < Width - 1; XIndex++)
        {
            spring.SetMasse1Id(YIndex * Width + XIndex);
            spring.SetMasse2Id((YIndex + 1) * Width + XIndex + 1);
            spring.SetStiffness(1.0);
            spring.SetFreeLength(1.4142);
            Network.AddSpring(spring);

            spring.SetMasse1Id((YIndex + 1) * Width + XIndex);
            spring.SetMasse2Id(YIndex * Width + XIndex + 1);
            spring.SetStiffness(1.0);
            spring.SetFreeLength(1.4142);
            Network.AddSpring(spring);
        }
    }

    Triangle t1temp, t2temp;
    for(YIndex = 0; YIndex < (Depth - 1); YIndex++)
    {
        for(XIndex = 0; XIndex < (Width - 1); XIndex++)
        {
            t1temp.SetMass1Id(YIndex * Width + XIndex);
            t1temp.SetMass2Id(YIndex * Width + XIndex + 1);
            t1temp.SetMass3Id((YIndex + 1) * Width + XIndex + 1);

            t2temp.SetMass1Id(YIndex * Width + XIndex);
            t2temp.SetMass2Id((YIndex + 1) * Width + XIndex + 1);
            t2temp.SetMass3Id((YIndex + 1) * Width + XIndex);

            Network.AddTriangle(t1temp);
            Network.AddTriangle(t2temp);
        }
    }

    Generate();
}

void AClothActor::Generate()
{
    TArray<FVector> Positions;
    TArray<FRuntimeMeshVertexNoPosition> VertexData;
    TArray<int32> Triangles;

    // Oversized bounding box so we don't have to update it
    BoundingBox = FBox(FVector(-HalfWidth, -HalfWidth, -100), FVector(HalfWidth, HalfWidth, 100));

    float Scale = CellSize / 50.0f;
    // Create the vertex array
    for(int32 YIndex = 0; YIndex < Depth; YIndex++)
    {
        for(int32 XIndex = 0; XIndex < Width; XIndex++)
        {
            Positions.Add(Network.GetMass(YIndex * Width + XIndex).GetPosition());
            VertexData.Add(FRuntimeMeshVertexNoPosition(FVector(0, 0, 1), FRuntimeMeshTangent(-1, 0, 0), FVector2D(XIndex * Scale, YIndex * Scale)));
        }
    }

    // Create the triangle array
    URuntimeMeshLibrary::CreateGridMeshTriangles(Width, Depth, true, Triangles);

    // Here we're going to use a dual buffer section for performance since we'll be updating positions only each frame
    RuntimeMesh->CreateMeshSectionDualBuffer(0, Positions, VertexData, Triangles, BoundingBox, false, EUpdateFrequency::Frequent);
}

// Called every frame
void AClothActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    Network.Update(DeltaTime);

    /*float AnimationStepX = 5;
    float AnimationStepY = 6;

    AnimationOffsetX += DeltaTime * AnimationStepX;
    AnimationOffsetY += DeltaTime * AnimationStepY;*/

    // Start position only update
    TArray<FVector>& Positions = *RuntimeMesh->BeginMeshSectionPositionUpdate(0);

    ParallelFor((Width)*(Depth), [this, &Positions](int32 Index) {
        int32 PlaneWidth = Width;
        int32 XIndex = Index % PlaneWidth;
        int32 YIndex = Index / PlaneWidth;

        float Scale = CellSize / 50.0f;

        //float HeightScale = FMath::Cos((XIndex * Scale) + AnimationOffsetX) + FMath::Sin((YIndex * Scale) + AnimationOffsetY);

        //Positions[Index].Z = HeightScale * Height;
        Positions[Index] = Network.GetMass(Index).GetPosition();
    });

    // Commit position only update (sends updates to GPU)
    RuntimeMesh->EndMeshSectionPositionUpdate(0, BoundingBox);
}