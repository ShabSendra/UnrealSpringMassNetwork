#pragma once

class RMC_EXAMPLES_API Spring
{

private:
    int32       Mass1Id;
    int32       Mass2Id;
    double      Stiffness;
    double      FreeLength;

public:
    Spring();
    ~Spring();

public:
    void    SetStiffness(double NewStiffness);
    double  GetStiffness() const;

    void    SetFreeLength(double NewFreeLength);
    double  GetFreeLength() const;

    void    SetMasse1Id(int32 Id);
    double  GetMasse1Id() const;

    void    SetMasse2Id(int32 Id);
    double  GetMasse2Id() const;
};
