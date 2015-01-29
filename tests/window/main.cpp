#include <wookie/RenderSystem.h>
#include <wookie/Renderable.h>
#include <wookie/Engine.h>
#include <iostream>

template<class T>
class TD;

struct Position : Component<Position> {};
struct Direction : Component<Direction> {};

int main() {
    Engine e;
    auto r = std::make_unique<RenderSystem>(6);

    auto& world = e.world();

    world.addSystem<RenderSystem>(std::move(r));

    auto& obj = world.create();

    auto& tileMap = world.create();

    Position c1;
    Position c2;
    Direction c3;
    Renderable c4 {{{-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}}};

    obj.add(c1, c4);
    auto o = obj.get<Position>();

    std::cerr << std::boolalpha;
    std::cerr << obj.hasComponents<Renderable>();
    std::cerr << obj.hasComponents<Position>();
    std::cerr << obj.hasComponents<Position, Direction>();

    //obj.remove<Direction>();

    std::cerr << std::endl;
    std::cerr << obj.hasComponents<Direction>();
    std::cerr << obj.hasComponents<Position>();
    std::cerr << obj.hasComponents<Position, Direction>();

    auto& obj2 = world.objectsById(0);

    auto oo = world.objectsByComponents<Position>();

    if (!oo.empty())
        std::cerr << std::endl << (oo[0])->hasComponents<Position>();
    //world.remove(obj2);

    std::cerr << std::endl;
    std::cerr << obj2.hasComponents<Direction>();
    std::cerr << obj2.hasComponents<Position>();
    std::cerr << obj2.hasComponents<Position, Direction>();


    //TD<decltype(o)> objtype;
    //std::cerr << c1.group().to_string() << " " << c2.group().to_string() << " " << c3.group().to_string();

    e.setup();
    e.run();
    e.shutdown();

    return 0;
}
