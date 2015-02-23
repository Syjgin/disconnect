#include "LevelConfigReader.h"
#include "XMLElement.h"

LevelConfigReader::LevelConfigReader(Urho3D::Context *context) : Object(context)
{
    context_ = context;
}


void LevelConfigReader::ReadConfig(Urho3D::XMLFile *config)
{
    XMLElement rootEl = config->GetRoot();
    _minimalBuildingsDist =  rootEl.GetChild("minimalBuildingsDist").GetFloat("val");
    _minimalRouterCount = rootEl.GetChild("minimalRouterCount").GetInt("val");
    _mapDimenstion = rootEl.GetChild("mapDimension").GetInt("val");

    _buildings.clear();
    XPathQuery buildingsQuery("*/building", "ResultSet");
    XPathResultSet results = buildingsQuery.Evaluate(rootEl);
    for(int i=0; i < results.Size(); i++)
    {
        String buildingKey = results[i].GetAttribute("name");
        int buildingCount = results[i].GetInt("count");
        _buildings.insert(std::pair<String,int>(buildingKey, buildingCount));
    }

    XPathQuery garbageQuery("*/garbageElement", "ResultSet");
    XPathResultSet garbageRes = garbageQuery.Evaluate(rootEl);
    for(int i=0; i < garbageRes.Size(); i++)
    {
        String buildingKey = garbageRes[i].GetAttribute("name");
        int buildingCount = garbageRes[i].GetInt("count");
        _garbage.insert(std::pair<String,int>(buildingKey, buildingCount));
    }
}
