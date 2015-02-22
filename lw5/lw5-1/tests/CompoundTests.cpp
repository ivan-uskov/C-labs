#include "stdafx.h"
#include "../body_hierarchy/Compound.h"
#include "../body_hierarchy/Cone.h"
#include "../body_hierarchy/Cylinder.h"
#include "../body_hierarchy/Sphere.h"
#include "../body_hierarchy/Parallelepiped.h"

using namespace std;

struct CompoundFixture
{
    CCompound compound;
};

BOOST_FIXTURE_TEST_SUITE(CCompoundTests, CompoundFixture)

/*
    Объем составного тела - сумма объёмов входящих в него тел
    Масса составного тела - сумма масс входящих в него тел
    Плотность составного тела - отношение суммарной массы к суммарнуму объему
*/
BOOST_AUTO_TEST_CASE(CompoundWith2Elements)
{
    CSphere sphere(5, 6);
    CParallelepiped parral(1, 2, 3, 4);

    compound.AddBody(sphere);
    compound.AddBody(parral);

    auto mass = sphere.GetMass() + parral.GetMass();
    auto volume = sphere.GetVolume() + parral.GetVolume();

    BOOST_CHECK(CheckDoublesAreEqual(compound.GetMass(), mass));
    BOOST_CHECK(CheckDoublesAreEqual(compound.GetVolume(), volume));
    BOOST_CHECK(CheckDoublesAreEqual(compound.GetDensity(), mass / volume));
}

BOOST_AUTO_TEST_SUITE_END()