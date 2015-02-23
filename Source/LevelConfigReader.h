#pragma once

#include "Object.h"
#include "XMLFile.h"
#include <map>

using namespace Urho3D;

class LevelConfigReader : public Object
{
  OBJECT(LevelConfigReader);
public:
    LevelConfigReader(Context* context);
    void ReadConfig(XMLFile *config);
    std::map<String, int> GetBuildings() { return _buildings; }
    std::map<String, int> GetGarbage() { return _garbage; }
    float GetMinimalBuildingsDist() { return _minimalBuildingsDist; }
    int GetMinimalRouterCount() { return _minimalRouterCount; }
    int GetMapDimension() { return _mapDimenstion; }
private:
    float _minimalBuildingsDist;
    int _minimalRouterCount;
    int _mapDimenstion;
    std::map<String, int> _buildings;
    std::map<String, int> _garbage;
};
