#include "stdafx.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"

using namespace std;

typedef vector<shared_ptr<CBody>> CBodyContainer;

pair<string, vector<double>> ParseShape(string str)
{
    pair<string, vector<double>> params;
    istringstream istrm(str);
    istrm >> params.first; // Get shape Name

    double arg;
    while (istrm >> arg) // Get shape constructor arguments
    {
        params.second.push_back(arg);
    }

    return params;
}

void AddShape(CBodyContainer & shapes, string const& shapeName, vector<double> const& args)
{
    if (shapeName == "Sphere")
    {
        if (args.size() == 2)
            shapes.push_back(make_shared<CSphere>(args[0], args[1]));
        else if (args.size() == 1)
            shapes.push_back(make_shared<CSphere>(args[0]));
        else
            throw invalid_argument("Create Sphere with this arguments impossibly!");
    }
    else if (shapeName == "Parallelepiped")
    {
        if (args.size() == 4)
            shapes.push_back(make_shared<CParallelepiped>(args[0], args[1], args[2], args[3]));
        else if (args.size() == 3)
            shapes.push_back(make_shared<CParallelepiped>(args[0], args[1], args[2]));
        else
            throw invalid_argument("Create Parallelepiped with this arguments impossibly!");
    }
    else if (shapeName == "Cone")
    {
        if (args.size() == 3)
            shapes.push_back(make_shared<CCone>(args[0], args[1], args[2]));
        else if (args.size() == 2)
            shapes.push_back(make_shared<CCone>(args[0], args[1]));
        else
            throw invalid_argument("Create Cone with this arguments impossibly!");
    }
    else if (shapeName == "Cylinder")
    {
        if (args.size() == 3)
            shapes.push_back(make_shared<CCylinder>(args[0], args[1], args[2]));
        else if (args.size() == 2)
            shapes.push_back(make_shared<CCylinder>(args[0], args[1]));
        else
            throw invalid_argument("Create Cylinder with this arguments impossibly!");
    }
    else
    {
        throw invalid_argument("Unknown shape!");
    }
}

CBodyContainer ReadShapes()
{
    CBodyContainer shapes;
    string str;

    while (!cin.fail())
    {
        cout << "> ";
        getline(cin, str);
        auto shapeParams = ParseShape(str);

        try
        {
            AddShape(shapes, shapeParams.first, shapeParams.second);
            cout << "Shape added!" << endl;
        }
        catch (invalid_argument const& e)
        {
            cout << e.what() << endl;
        }
    }

    return shapes;
}

CBody const& GetShapeWithMaxWeight(CBodyContainer const& shapes)
{
    CBody const* pMaxBody = nullptr;
    
    for_each(shapes.begin(), shapes.end(), [&pMaxBody](shared_ptr<CBody> const& pShape)
    {
        if (pMaxBody == nullptr || pMaxBody->GetWeight() < pShape->GetWeight())
        {
            pMaxBody = pShape.get();
        }
    });

    return *pMaxBody;
}


// сила с которой объект действует на нижние слои воды
double GetWeightInWater(CBody const& shape)
{
    static const double WATER_DENSITY = 1000;
    static const double GRAVITY       = 9.8;

    return GRAVITY * (shape.GetWeight() - WATER_DENSITY * shape.GetVolume());
}

CBody const& GetShapeWithMinWeightInWater(CBodyContainer const& shapes)
{
    CBody const* pMinBody = nullptr;

    for_each(shapes.begin(), shapes.end(), [&pMinBody](shared_ptr<CBody> const& pShape)
    {
        if (pMinBody == nullptr || GetWeightInWater(*pMinBody) > GetWeightInWater(*pShape))
        {
            pMinBody = pShape.get();
        }
    });

    return *pMinBody;
}

int main(int argc, char* argv[])
{
    cout << "Enter shape name with constructor arguments!" << endl;

    auto shapes = ReadShapes();

    cout << "Shape with maximal weight:" << endl;
    cout << GetShapeWithMaxWeight(shapes).ToString();

    cout << "Shape with minimal weight in water:" << endl;
    cout << GetShapeWithMinWeightInWater(shapes).ToString();

    cout << "Bye!" << endl;

    return 0;
}

