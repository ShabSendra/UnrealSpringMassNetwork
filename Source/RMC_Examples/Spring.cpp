#include "RMC_Examples.h"
#include "Spring.h"

Spring::Spring()
{
}

Spring::~Spring()
{
}

void    Spring::SetStiffness(double NewStiffness)
{
    Stiffness = NewStiffness;
}

double  Spring::GetStiffness() const
{
    return Stiffness;
}

void    Spring::SetFreeLength(double NewFreeLength)
{
    FreeLength = NewFreeLength;
}

double  Spring::GetFreeLength() const
{
    return FreeLength;
}

void    Spring::SetMasse1Id(int32 Id)
{
    Mass1Id = Id;
}

double  Spring::GetMasse1Id() const
{
    return Mass1Id;
}

void    Spring::SetMasse2Id(int32 Id)
{
    Mass2Id = Id;
}

double  Spring::GetMasse2Id() const
{
    return Mass2Id;
}