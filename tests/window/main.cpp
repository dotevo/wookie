#include <wookie/core/Engine.h>
#include <wookie/rendering/GL/GLcontext.h>
#include <wookie/rendering/GL/GLrenderer.h>
#include <wookie/rendering/RenderSystem.h>

#include <iostream>

template<class T>
class TD;

struct Position : Component<Position> {};
struct Direction : Component<Direction> {};

int main() {
    Engine e;
    auto r = std::make_unique<RenderSystem>(std::make_unique<GLcontext>(),std::make_unique<GLrenderer>(), 6);

    auto& world = e.world();

    world.addSystem<RenderSystem>(std::move(r));

    auto& tile = world.create();

    Position c1;
    Position c2;
    Direction c3;

    //Vertex v1 {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}};
    //Vertex v2 {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}};
    //Vertex v3 {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    //Vertex v4 {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}};

    Image img("tile.png");

    for (int i = 0; i < 64; ++i) {
        for (int j = 64; j>0; --j) {
            Renderable c4 {std::make_unique<Tile>(j, i, img)};
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

    //TD<decltype(o)> objtype;
    //std::cerr << c1.group().to_string() << " " << c2.group().to_string() << " " << c3.group().to_string();

    e.setup();
    e.run();
    e.shutdown();

    return 0;
}
