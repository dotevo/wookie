#include <wookie/core/Engine.h>
#include <wookie/rendering/RenderSystem.h>
#include <wookie/rendering/Renderable.h>
#include <wookie/rendering/SDL/SDLcontext.h>
#include <wookie/rendering/SDL/SDLrenderer.h>
#include <wookie/item/ItemManager.h>
#include <wookie/resource/ResourceManager.h>

#include <iostream>

struct Position : Component<Position> {};
struct Direction : Component<Direction> {};


int main() {
    Engine e;
    auto r = std::make_unique<RenderSystem>(std::make_unique<SDLcontext>(),std::make_unique<SDLrenderer>( ), 6);

    ResourceManager *rm = new ResourceManager();
    ItemManager *im = new ItemManager(rm);
    im->load("resources/set1/obj.json");
    im->getItem("tiles","grass");


    auto& world = e.world();

    world.addSystem<RenderSystem>(std::move(r));

    auto& obj = world.create();

    auto& tile = world.create();

    Position c1;
    Position c2;
    Direction c3;

    Vertex v1 {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}};
    Vertex v2 {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}};
    Vertex v3 {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    //Vertex v4 {{0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}};

    Renderable c4 {{v1, v2, v3}};
    obj.add(c4);

    e.setup();
    e.run();
    e.shutdown();

    return 0;
}
