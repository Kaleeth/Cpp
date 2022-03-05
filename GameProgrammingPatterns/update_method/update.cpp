class Entity { 
public:
    Entity()
    : x_(0), y_(0)
    {}

    virtual ~Entity() {}
    virtual void update() = 0;

    double x() const { return x_; }
    double y() const { return y_; }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

private:
    double x_;
    double y_;
};
// consider using components rather than inheritance
// and update method would be called on components of entity
class Skeleton : public Entity { 
public:
    Skeleton()
    : patrollingLeft_(false)
    {}
    
    virtual void update() {
        if (patrollingLeft_) {
            setX(x() - 1);
            if (x() == 0) patrollingLeft_ = false;
        }
        else {
            setX(x() + 1);
            if (x() == 100) patrollingLeft_ = true;
        }
    }
private:
    bool patrollingLeft_;
};
class Statue : public Entity { 
public:
    Statue(int delay)
    : frames_(0),
    delay_(delay)
    {}
    
    virtual void update() {
        if (++frames_ == delay_) {
            shootLightning();
            // Reset the timer.
            frames_ = 0;
        }
    }
private:
    int frames_;
    int delay_;
    void shootLightning()
    {
        // Shoot the lightning...
    }
};

class World { 
public:
    World()
    : numEntities_(0)
    {}

    void gameLoop();
    
private:
    Entity* entities_[MAX_ENTITIES]; // consider rather an actual collection
    int numEntities_;
};

void World::gameLoop() {
    while (true) {
        // Handle user input...
        // Update each entity.
        for (int i = 0; i < numEntities_; i++) {
            entities_[i]->update();
        }
        // Physics and rendering...
    }
}