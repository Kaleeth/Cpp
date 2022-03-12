class Actor {
public:
    Actor() : currentSlapped_(false) {}
    
    virtual ~Actor() {}
    virtual void update() = 0;

    void swap() {
        // Swap the buffers
        currentSlapped_ = nextSlapped_;
        // Clear the new "next" buffer
        nextSlapped_ = false;
    }

    void slap() { nextSlapped_ = true; }
    bool wasSlapped() { return currentSlapped_; }
private:
    bool currentSlapped_;
    bool nextSlapped_;
};
class Comedian : public Actor {
public:
    void face(Actor* actor) { facing_ = actor; }
    virtual void update() { 
        if (wasSlapped()) facing_->slap();
    }
private:
    Actor* facing_;
};

class Stage { 
public:
    void add(Actor* actor, int index) {
        actors_[index] = actor;
    }
    void update();
private:
    static const int NUM_ACTORS = 3;
    Actor* actors_[NUM_ACTORS];
};
void Stage::update() {
    for (int i = 0; i < NUM_ACTORS; i++) {
        actors_[i]->update();
    }
    for (int i = 0; i < NUM_ACTORS; i++) {
        actors_[i]->swap();
    }
}

int main(int argc, char const *argv[]) {
    Stage stage;
    Comedian* harry = new Comedian();
    Comedian* baldy = new Comedian();
    Comedian* chump = new Comedian();
    harry->face(baldy);
    baldy->face(chump);
    chump->face(harry);
    stage.add(harry, 0);
    stage.add(baldy, 1);
    stage.add(chump, 2);

    harry->slap();
    stage.update();

    return 0;
}

// semi monolithic alternative if knowledge of old buffer not required while updating
class Actor { 
public:
    static void init() { current_ = 0; }
    static void swap() { current_ = next(); } // ? + slapped_[current] = false;
    
    void slap() { slapped_[next()] = true; }
    bool wasSlapped() { return slapped_[current_]; }
private:
    static int current_;
    static int next() { return 1 - current_; }
    
    bool slapped_[2];
};