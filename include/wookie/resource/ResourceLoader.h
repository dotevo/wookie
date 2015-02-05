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
    ResourceLoader() {}
    virtual ~ResourceLoader() {}

    std::shared_ptr<T> load(const std::string &name);
};

template<typename T>
std::shared_ptr<T> ResourceLoader<T>::load(const std::string &name) {
      return std::make_shared<T>(name);
}
