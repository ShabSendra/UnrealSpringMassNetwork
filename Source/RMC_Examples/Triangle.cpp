// Copyright 2016 Chris Conway (Koderz). All Rights Reserved.

#include "RMC_Examples.h"
#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void    Triangle::SetMass1Id(const int &Id)
{
    Mass1Id = Id;
}
int     Triangle::GetMass1Id() const
{
    return Mass1Id;
}
void    Triangle::SetMass2Id(const int &Id)
{
    Mass2Id = Id;

}
int     Triangle::GetMass2Id() const
{
    return Mass2Id;
}
void    Triangle::SetMass3Id(const int &Id)
{
    Mass3Id = Id;
}
int     Triangle::GetMass3Id() const
{
    return Mass3Id;
}