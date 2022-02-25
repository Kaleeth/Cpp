typedef Monster* (*SpawnCallback)();

class Monster {
public:
    virtual ~Monster() {}
    // virtual Monster* clone() = 0;
    
    // Other stuff...
};
class Ghost : public Monster {
public:
    Ghost(int health, int speed) : health_(health), speed_(speed) {}
    // virtual Monster* clone() {
    //     return new Ghost(health_, speed_);
    // }
private:
    int health_;
    int speed_;
};

Monster* spawnGhost()
{
    return new Ghost(0, 0);
}

class Spawner { 
public:
    Spawner(SpawnCallback spawn) : spawn_(spawn) {}
    Monster* spawnMonster() {
        return spawn_();
    }
private:
    SpawnCallback spawn_;
};

int main() {
    Spawner* ghostSpawner = new Spawner(spawnGhost);
}