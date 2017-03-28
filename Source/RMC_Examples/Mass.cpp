// Copyright 2016 Chris Conway (Koderz). All Rights Reserved.

#include "RMC_Examples.h"
#include "Mass.h"


Mass::Mass(double mass, const FVector &position, const FVector &velocity, const FVector &force)
    : bIsFixed{false}, m{mass}, Position{position}, Velocity{velocity}, Force{force}
{}

Mass::~Mass()
{}

void Mass::SetIsFixed(bool b)
{
    bIsFixed = b;
}

void Mass::SetMass(double mass)
{
    m = mass;
}

double Mass::GetMass() const
{
    return m;
}

void Mass::SetPosition(float x, float y, float z)
{
    if(!bIsFixed)
    {
        Position.X = x;
        Position.Y = y;
        Position.Z = z;
    }
}

void Mass::SetPosition(const FVector& NewPosition)
{
    if(!bIsFixed)
    {
        Position = NewPosition;
    }
}

const FVector& Mass::GetPosition() const
{
    return Position;
}

void Mass::SetVelocity(float x, float y, float z)
{
    Velocity.X = x;
    Velocity.Y = y;
    Velocity.Z = z;
}

void Mass::SetVelocity(const FVector& NewVelocity)
{
    Velocity = NewVelocity;
}

const FVector& Mass::GetVelocity() const
{
    return Velocity;
}

void Mass::SetForce(float x, float y, float z)
{
    Force.X = x;
    Force.Y = y;
    Force.Z = z;
}

void Mass::SetForce(const FVector& NewForce)
{
    Force = NewForce;
}

const FVector &Mass::GetForce() const
{
    return Force;
}

void Mass::AddForce(float x, float y, float z)
{
    Force += FVector(x, y, z);
}

void Mass::AddForce(const FVector& v)
{
    Force += v;
}
