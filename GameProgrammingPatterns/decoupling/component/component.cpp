class Sprite; class World; class Graphics; class Volume; class Controller;

class InputComponent {
public:
    virtual ~InputComponent() {}
    virtual void update(GameObject& bjorn) = 0;
};
class PhysicsComponent { 
public:
    virtual ~PhysicsComponent() {}
    virtual void update(GameObject& obj, World& world) = 0;
};
class GraphicsComponent { 
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject& obj, Graphics& graphics) = 0;
};

class PlayerInputComponent : public InputComponent { 
public:
    virtual void update(GameObject& bjorn) {
        switch (Controller::getJoystickDirection()) {
        case DIR_LEFT:
            bjorn.velocity -= WALK_ACCELERATION;
            break;
        case DIR_RIGHT:
            bjorn.velocity += WALK_ACCELERATION;
            break;
        }
    }
private:
    static const int WALK_ACCELERATION = 1;
};

class DemoInputComponent : public InputComponent { 
public:
    virtual void update(GameObject& bjorn) {
        // AI to automatically control Bjorn...
    }
};

class PlayerPhysicsComponent : public PhysicsComponent {
public:
    void update(GameObject& g_obj, World& world) {
        g_obj.x += g_obj.velocity;
        world.resolveCollision(volume_, g_obj.x, g_obj.y, g_obj.velocity);
    }
private:
    Volume volume_;
};

class PlayerGraphicsComponent : public GraphicsComponent { 
public:
    void update(GameObject& g_obj, Graphics& graphics) {
        Sprite* sprite = &spriteStand_;
        if (g_obj.velocity < 0) {
            sprite = &spriteWalkLeft_;
        }
        else if (g_obj.velocity > 0) {
            sprite = &spriteWalkRight_;
        }
        graphics.draw(*sprite, g_obj.x, g_obj.y);
    }
private:
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};

class GameObject { 
public:
    int velocity;
    int x, y;

    GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
    : input_(input), physics_(physics), graphics_(graphics) {}

    void update(World& world, Graphics& graphics) {
        input_->update(*this);
        physics_->update(*this, world);
        graphics_->update(*this, graphics);
    }
    GameObject* createBjorn() { // example of factory method
        return new GameObject(new PlayerInputComponent(), new PlayerPhysicsComponent(), new PlayerGraphicsComponent());
    }

private:
    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};

int main() {
    GameObject* gameObject = new GameObject(new PlayerInputComponent(), new PlayerPhysicsComponent(), new PlayerGraphicsComponent());
    GameObject* bjorn = gameObject->createBjorn();
}