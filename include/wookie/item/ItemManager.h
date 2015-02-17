#pragma once

#include <map>
#include <string>
#include <memory>
#include <json/json.h>

#include <wookie/core/WObject.h>

class ResourceManager;
class Item;

class ItemManager :public WObject
{
public:
    ItemManager(ResourceManager *rm);
    virtual ~ItemManager();

    bool load(std::string path);
    std::shared_ptr<Item> getItem(std::string name_space, std::string name);
private:
    bool addItemToEnv(std::string name_space, std::string name, std::string path);
    bool loadItem(std::string name_space, std::string name);
    void parseImage(Item* item, Json::Value value,std::string path);

    ResourceManager * mResourceManager;
    //Namespace/Name/Path
    std::map< std::string, std::map<std::string, std::string > >  objPath;
    //Namespace/Name/Loaded item
    std::map< std::string, std::map<std::string, std::shared_ptr<Item> > >  items;
};
