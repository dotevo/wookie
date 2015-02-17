#include <wookie/core/Engine.h>
#include <wookie/rendering/RenderSystem.h>
#include <wookie/game/isometric/Renderable.h>
#include <wookie/rendering/SDL/SDLcontext.h>
#include <wookie/rendering/SDL/SDLTileRenderer.h>
#include <wookie/item/ItemManager.h>
#include <wookie/resource/ResourceManager.h>
#include <wookie/rendering/Camera.h>

#include <iostream>

struct Position : Component<Position> {};
struct Direction : Component<Direction> {};


int main() {
    Engine e;
    auto rc = std::make_unique<SDLcontext>();

    rc->onClose.connect(&e,&Engine::close);
    auto r = std::make_unique<RenderSystem>(std::move(rc),std::make_unique<SDLTileRenderer>( ), 6);

    ResourceManager *rm = new ResourceManager();
    ItemManager *im = new ItemManager(rm);
    im->load("resources/set1/obj.json");
    im->getItem("tiles","grass");


    auto& world = e.world();

    world.addSystem<RenderSystem>(std::move(r));

    auto& camera = world.create();

    Position c1;
    Position c2;
    Direction c3;
    Camera c4;

    camera.add(c4);

    Image img("resources/set1/grass/45.png");

    for (int i = 0; i < 8; ++i) {
        for (int j = 8; j > 0; --j) {
            Renderable c4 {i, j, &img};
            auto& obj = world.create();
            obj.add(c4);
        }
    }

    auto& obj2 = world.objectsById(0);

    auto oo = world.objectsByComponents<Position>();

    if (!oo.empty())
        std::cerr << std::endl << (oo[0])->hasComponents<Position>();
    //world.remove(obj2);

    std::cerr << std::endl;
    std::cerr << obj2.hasComponents<Direction>();
    std::cerr << obj2.hasComponents<Position>();
    std::cerr << obj2.hasComponents<Position, Direction>();



    e.setup();
    e.run();
    e.shutdown();

    return 0;
}
