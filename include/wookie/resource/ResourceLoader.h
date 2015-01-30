#pragma once

#include <map>
#include <string>
#include <memory>
#include <iostream>

#include <wookie/core/WObject.h>

template<typename T>
class ResourceLoader :public WObject
{
public:
    ResourceLoader(const std::string &basePath);
    virtual ~ResourceLoader() {}

    std::shared_ptr<T> load(const std::string &name);
private:
    std::string basePath;
};
