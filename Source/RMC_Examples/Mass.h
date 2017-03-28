#pragma once

class RMC_EXAMPLES_API Mass
{

private:
    bool    bIsFixed;
    double  m;
    FVector Position;
    FVector Velocity;
    FVector Force;

public:
    Mass(double mass = 1.0, const FVector& position = FVector::ZeroVector, const FVector& velocity = FVector::ZeroVector, const FVector& force = FVector::ZeroVector);
    ~Mass();

public:
    void    SetIsFixed(bool b);

    void    SetMass(double mass);
    double  GetMass() const;

    void    SetPosition(float x, float y, float z);
    void    SetPosition(const FVector& NewPosition);
    const   FVector &GetPosition() const;

    void    SetVelocity(float x, float y, float z);
    void    SetVelocity(const FVector& NewVelocity);
    const   FVector &GetVelocity() const;

    void    SetForce(float x, float y, float z);
    void    SetForce(const FVector& NewForce);
    const   FVector &GetForce() const;

    void    AddForce(float x, float y, float z);
    void    AddForce(const FVector& f);


};
