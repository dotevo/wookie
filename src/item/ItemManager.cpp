#include <fstream>
#include <iostream>

#include <wookie/resource/Image.h>
#include <wookie/item/Item.h>
#include <wookie/item/ItemManager.h>
#include <wookie/resource/ResourceManager.h>

ItemManager::ItemManager(ResourceManager *rm)
    :mResourceManager(rm){
}

ItemManager::~ItemManager() {
}

bool ItemManager::load(std::string path) {
    std::ifstream in(path);
    if (!in.is_open()){
        std::cout << "Failed to open "<< path <<'\n';
        return false;
    }

    Json::Value json;
    in >> json;
    std::string npath = path.substr(0, path.find_last_of("\\/"));
    //Array of objects
    if(json.isArray()){
        for(Json::ArrayIndex i=0;i<json.size();i++){
            Json::Value obj = json.get(i,"");
            Json::Value name = obj.get("name","");
            Json::Value name_space = obj.get("namespace","");
            Json::Value path = obj.get("path","");
            addItemToEnv(name_space.asString(), name.asString(), npath+"/"+path.asString());
        }
    }
    in.close();
    return true;
}

std::shared_ptr<Item> ItemManager::getItem(std::string name_space, std::string name) {
    //If not loaded
    if(items.count(name_space) == 0 || items[name_space].count(name) == 0) {
        std::cout << "Need to be loaded" << std::endl;
        if(!loadItem(name_space,name)){
            return nullptr;
        }
    }
    return items[name_space][name];
}

bool ItemManager::addItemToEnv(std::string name_space, std::string name, std::string path) {
    std::cout << "New Object " << name_space << ":" << name << " (" << path << ")" << std::endl;
    objPath[name_space][name] = path;
    return true;
}

bool ItemManager::loadItem(std::string name_space, std::string name){
    if(objPath.count(name_space) == 0 || objPath[name_space].count(name) == 0) {
        std::cout << "NOT FOUND" << std::endl;
        return false;
    }
    std::string npath = objPath[name_space][name].substr(0, objPath[name_space][name].find_last_of("\\/"));
    std::ifstream in(objPath[name_space][name]);
    if (!in.is_open()){
        std::cout << "Failed to open "<< objPath[name_space][name] <<'\n';
        return false;
    }
    Json::Value json;
    in >> json;
    auto *item=new Item();
    //Images
    auto images = json.get("resources","");
    if(images.isArray()){
        for(Json::ArrayIndex i=0;i<images.size();i++){
            auto obj = images.get(i,"");
            auto type = obj.get("type","");
            if(type.isString()){
                if(type.asString().compare("image")==0){
                    parseImage(item,obj,npath);
                }else if(type.asString().compare("atlas")==0){
                    //TODO
                }
            }
        }
    }
    std::shared_ptr<Item> obj(item);
    items[name_space][name] = obj;
    in.close();
    return true;
}

void ItemManager::parseImage(Item* item,Json::Value value,std::string npath){
    auto path = value.get("path","");
    mResourceManager->load<Image>(npath+"/"+path.asString());
}
