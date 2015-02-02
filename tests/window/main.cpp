#include <wookie/core/Engine.h>
#include <wookie/rendering/GL/GLrenderer.h>
#include <wookie/rendering/RenderSystem.h>

#include <iostream>

template<class T>
class TD;

struct Position : Component<Position> {};
struct Direction : Component<Direction> {};

int main() {
    Engine e;
    auto r = std::make_unique<RenderSystem>(std::make_unique<GLrenderer>(), 6);

    auto& world = e.world();

    world.addSystem<RenderSystem>(std::move(r));

    auto& obj = world.create();

    auto& tile = world.create();

    Position c1;
    Position c2;
    Direction c3;

    Vertex v1 {{-0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    Vertex v2 {{-0.2f, 0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    Vertex v3 {{0.2f, 0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    Vertex v4 {{0.2f, -0.2f, 0.0f}, {0.0f, 0.0f, 0.0f}};

    Renderable c4 {{v1, v2, v3}};

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
