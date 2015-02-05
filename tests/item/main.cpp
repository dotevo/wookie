#include <wookie/core/Engine.h>
#include <wookie/rendering/RenderSystem.h>
#include <wookie/rendering/Renderable.h>

#include <wookie/item/ItemManager.h>
#include <wookie/resource/ResourceManager.h>

#include <iostream>

int main() {
    ResourceManager *rm = new ResourceManager();
    ItemManager *im = new ItemManager(rm);
    im->load("resources/set1/obj.json");
    im->getItem("tiles","grass");

    return 0;
}
