#include <wookie/core/Engine.h>
#include <wookie/rendering/RenderSystem.h>
#include <wookie/game/isometric/Renderable.h>
#include <wookie/rendering/SDL/SDLcontext.h>
#include <wookie/rendering/SDL/SDLTileRenderer.h>
#include <wookie/item/ItemManager.h>
#include <wookie/resource/ResourceManager.h>

#include <iostream>

struct Position : Component<Position> {};
struct Direction : Component<Direction> {};


int main() {
    Engine e;
    auto r = std::make_unique<RenderSystem>(std::make_unique<SDLcontext>(),std::make_unique<SDLTileRenderer>( ), 6);

    ResourceManager *rm = new ResourceManager();
    ItemManager *im = new ItemManager(rm);
    im->load("resources/set1/obj.json");
    im->getItem("tiles","grass");


    auto& world = e.world();

    world.addSystem<RenderSystem>(std::move(r));

    auto& obj = world.create();

    auto& tile = world.create();

    e.setup();
    e.run();
    e.shutdown();

    return 0;
}
