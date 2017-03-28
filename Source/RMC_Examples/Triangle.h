// Copyright 2016 Chris Conway (Koderz). All Rights Reserved.

#pragma once

/**
 * 
 */
class RMC_EXAMPLES_API Triangle
{
private:
    int32 Mass1Id;
    int32 Mass2Id;
    int32 Mass3Id;

public:
	Triangle();
	~Triangle();

    void    SetMass1Id(const int &Id);
    int     GetMass1Id() const;
    void    SetMass2Id(const int &Id);
    int     GetMass2Id() const;
    void    SetMass3Id(const int &Id);
    int     GetMass3Id() const;
};
