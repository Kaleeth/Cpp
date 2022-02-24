class Entity {};
enum Event {EVENT_ENTITY_FELL,};
enum Achievement {ACHIEVEMENT_FELL_OFF_BRIDGE,};
class Observer {
    friend class Subject;
public:
    Observer() : next_(nullptr) {}
    virtual ~Observer() {
        // subject->removeObserver(this); // observer should unsubscribe itself from subject if deletion is managed
    }
    // examplary parameters: Entity - object sending notification, Event - object about stuff that happened
    virtual void onNotify(const Entity& entity, Event event) = 0;
private:
    Observer* next_;
    // Observer* prev_; // consider doubly linked list
    // Subject* subject; // if we want to manage deletion etc. of observers
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
    Subject() : head_(nullptr) {}
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);

protected:
    void notify(const Entity& entity, Event event) {
        Observer* observer = head_;
        while (observer != nullptr) {
            observer->onNotify(entity, event);
            observer = observer->next_;
        }
    }   
      
private:
    Observer* head_;
    int numObservers_;
};
// pointer to a pointer impl
void Subject::addObserver(Observer* observer) {
    observer->next_ = head_;
    head_ = observer;
}
void Subject::removeObserver(Observer* observer) {
    Observer** current = &head_;
    while (*current != nullptr) {
        if (*current == observer) {
            *current = observer->next_;
            observer->next_ = nullptr;
            return;
        }
        current = &(*current)->next_;
    }
}
// WARNING!
// the implementation of Subject having list of Observers assumes an Observer belongs only to one Subject
// not a bad assumption but in case it is a problem, consider a "pool of list nodes"
// where instead of list of Observers, Subject has list of ListNodes each with a pointer to a chosen observer (SEE MODEL)

// example of implementing achievement related to game's physics
class Physics : public Subject { 
    // consider creating an instance of Subject inside Physics instead, e.g. separate "falling event" subject
    // then observers would do: physics.entityFell().addObserver(this);
public:
    void updateEntity(Entity& entity);
};