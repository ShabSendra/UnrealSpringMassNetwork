#include "RMC_Examples.h"
#include "MassSpringNetwork.h"

double Uniforme(const double& a, const double& b)
{
    double seedri;
    seedri = (double)rand() / RAND_MAX;
    return(seedri*(b - a) + a);
}

FVector generevent()
// Genere du vent aleatoire, appeler une seul fois par tranche de temps
{
    FVector v_wind = FVector::ZeroVector;
    static double vx = 5.0;
    static double vz = 0.0;

    vx += Uniforme(-2, 2);
    vz += Uniforme(-1, 1);

    if(vx < 2.0)
        vx = 2.0;

    if(vx > 5.0)
        vx = 5.0;

    if(vz < -3.0)
        vz = -3.0;

    if(vz > 3.0)
        vz = 3.0;

    v_wind = FVector(5.0, 0.0, 0.0);

    return v_wind;
}


const FVector MassSpringNetwork::Gravity(0.0, 0.0, -9.8);

MassSpringNetwork::MassSpringNetwork()
{}

MassSpringNetwork::~MassSpringNetwork()
{}

void MassSpringNetwork::AddMass(const Mass& mass)
{
    Masses.Add(mass);
}

void MassSpringNetwork::AddSpring(const Spring& spring)
{
    Springs.Add(spring);
}

void MassSpringNetwork::AddTriangle(const Triangle& triangle)
{
    Triangles.Add(triangle);
}

Mass& MassSpringNetwork::GetMass(int32 Index)
{
    return Masses[Index];
}

void MassSpringNetwork::Update(float DeltaTime)
{
    // Force = Mass * acceleration
    // g = acceleration du a la gravite terrestre
    // Poids = Mass * g;

    FVector vitesseVent = generevent() * 5.0;
    // FORCE EXTERIEUR
    for(int i = 0; i < Masses.Num(); ++i)
    {
        // La force du Poids
        FVector poids = Masses[i].GetMass() * Gravity;
        FVector friction = -MassAirFriction * Masses[i].GetVelocity();
        Masses[i].SetForce(poids + friction);
    }

    for(int i = 0; i < Triangles.Num(); ++i)
    {
        // La force du vent
        Triangle &triangle = Triangles[i];
        Mass &m1 = Masses[triangle.GetMass1Id()];
        Mass &m2 = Masses[triangle.GetMass2Id()];
        Mass &m3 = Masses[triangle.GetMass3Id()];

        FVector vitesseMoyenne = (1.0f / 3.0f) * (m1.GetVelocity() + m2.GetVelocity() + m3.GetVelocity());
        FVector normale = (m2.GetPosition() - m1.GetPosition()) ^ (m3.GetPosition() - m1.GetPosition());
        normale.Normalize();
        FVector forceVent = TriangleAirFriction * (normale * (vitesseVent - vitesseMoyenne)) * normale;
        m1.SetForce(m1.GetForce() + forceVent);
        m2.SetForce(m2.GetForce() + forceVent);
        m3.SetForce(m3.GetForce() + forceVent);
    }

    // FORCE INTERNE
    // Force ressorts
    for(int i = 0; i < Springs.Num(); ++i)
    {
        Mass &m1 = Masses[Springs[i].GetMasse1Id()];
        Mass &m2 = Masses[Springs[i].GetMasse2Id()];

        FVector m1m2 = m2.GetPosition() - m1.GetPosition();
        FVector SpringDir = FVector(m1m2);
        SpringDir.Normalize();
        double raideur = Springs[i].GetStiffness();

        FVector forceRessort = -raideur * (m1m2 - Springs[i].GetFreeLength() * SpringDir);
        m1.SetForce(m1.GetForce() - forceRessort);
        m2.SetForce(m2.GetForce() + forceRessort);
    }

    for(int i = 0; i < Masses.Num(); ++i)
    {
        FVector acceleration = (1 / Masses[i].GetMass()) * Masses[i].GetForce();
        FVector vitesse = Masses[i].GetVelocity() + acceleration * 0.009;
        Masses[i].SetVelocity(vitesse);
        Masses[i].SetPosition(Masses[i].GetPosition() + vitesse * 0.009);
    }
}
