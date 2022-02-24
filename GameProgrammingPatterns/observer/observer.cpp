class Entity {};
enum Event {EVENT_ENTITY_FELL,};
enum Achievement {ACHIEVEMENT_FELL_OFF_BRIDGE,};
class Observer {
public:
    virtual ~Observer() {}
    // examplary parameters: Entity - object sending notification, Event - object about stuff that happened
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

class Achievements : public Observer { 
public:
    virtual void onNotify(const Entity& entity, Event event) {
        switch (event) {
            case EVENT_ENTITY_FELL:
            if (entity.isHero() && heroIsOnBridge_) {
                unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
            }
            break;
            // Handle other events, and update heroIsOnBridge_...
        }
    }
private:
    void unlock(Achievement achievement) {
        // Unlock if not already unlocked...
    }
    bool heroIsOnBridge_;
};

// Subject - class notifying observers
class Subject {
public:
    void addObserver(Observer* observer) {
        // Add to array...
    }
    void removeObserver(Observer* observer) {
        // Remove from array...
    }

protected:
    void notify(const Entity& entity, Event event) {
        for (int i = 0; i < numObservers_; i++) {
            observers_[i]->onNotify(entity, event);
        }
    }   
      
private:
    Observer* observers_[MAX_OBSERVERS]; // use dynamically-sized collection like vector instead
    int numObservers_;
};

// example of implementing achievement related to game's physics
class Physics : public Subject { 
    // consider creating an instance of Subject inside Physics instead, e.g. separate "falling event" subject
    // then observers would do: physics.entityFell().addObserver(this);
public:
    void updateEntity(Entity& entity);
};