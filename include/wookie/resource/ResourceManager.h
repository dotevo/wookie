#pragma once

#include <map>
#include <string>
#include <memory>
#include <iostream>

#include <wookie/resource/Image.h>
#include <wookie/core/WObject.h>
#include <wookie/resource/Resource.h>
#include <wookie/resource/ResourceLoader.h>

enum RESOURCE_TYPE
{
    RESOURCE_TYPE_IMAGE
};

class ResourceManager :public WObject
{
public:
    ResourceManager();
    virtual ~ResourceManager();

    template<class T>
    std::enable_if_t <std::is_base_of<Resource, T>::value, bool>
    load(std::string path);
private:
    std::map< std::string, std::pair< int, std::shared_ptr<Resource> > > resources;
};

template<class T>
std::enable_if_t <std::is_base_of<Resource, T>::value, bool>
ResourceManager::load(std::string path){
    std::cout << "LOAD" << std::endl;
    if(resources.count(path)==0){
        ResourceLoader<T> loader;
        std::shared_ptr<T> a = loader.load(path);
        if(a != nullptr){
            resources[path] = std::pair<int, std::shared_ptr<T> > (1, a);
        }else{
            return false;
        }
    }else{
        std::cout << "Resource is loaded... skip" << std::endl;
    }
    return true;
}


