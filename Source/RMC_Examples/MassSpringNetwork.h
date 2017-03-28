#pragma once

#include "Mass.h"
#include "Spring.h"
#include "Triangle.h"


class RMC_EXAMPLES_API MassSpringNetwork
{
private:
    TArray<Mass> Masses;
    TArray<Spring> Springs;
    TArray<Triangle> Triangles;

    static const FVector Gravity;
    const double MassAirFriction = 0.01;
    const double TriangleAirFriction = 0.05;

public:
    MassSpringNetwork();
    ~MassSpringNetwork();

    void AddMass(const Mass& mass);
    void AddSpring(const Spring& spring);
    void AddTriangle(const Triangle& triangle);

    /*const Mass& GetMass(int32 Index);*/
    Mass& GetMass(int32 Index);

    void Update(float DeltaTime);
};
