#include <wookie/resource/ResourceLoader.h>

template<typename T>
ResourceLoader<T>::ResourceLoader(const std::string &basePath)
    :basePath(basePath) {
}

template<typename T>
std::shared_ptr<T> ResourceLoader<T>::load(const std::string &name) {
      return std::make_shared<T>(basePath + name);
}
