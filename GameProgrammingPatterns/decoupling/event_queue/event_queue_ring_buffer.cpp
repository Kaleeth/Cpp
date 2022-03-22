#include <cassert>

struct PlayMessage { SoundId id; int volume; };

class Audio { 
public:
    static void init() {
        head_ = 0;
        tail_ = 0;
    }
    // Methods...
    void playSound(SoundId id, int volume);

    void update();

private:
    static const int MAX_PENDING = 16;
    static PlayMessage pending_[MAX_PENDING];
    static int numPending_;

    static int head_;
    static int tail_;
    // Array...
};

void Audio::playSound(SoundId id, int volume) {
    // Walk the pending requests.
    for (int i = head_; i != tail_; i = (i + 1) % MAX_PENDING) {
        if (pending_[i].id == id) {
            // Use the larger of the two volumes.
            pending_[i].volume = max(volume, pending_[i].volume);
            // Don't need to enqueue.
            return;
        }
    }

    assert((tail_ + 1) % MAX_PENDING != head_);

    // Add to the end of the list.
    pending_[tail_].id = id;
    pending_[tail_].volume = volume;
    tail_ = (tail_ + 1) % MAX_PENDING;
}

void Audio::update() {
    // If there are no pending requests, do nothing.
    if (head_ == tail_) return;

    ResourceId resource = loadSound(pending_[head_].id);
    int channel = findOpenChannel();
    if (channel == -1) return;
    startSound(resource, channel, pending_[head_].volume);

    head_ = (head_ + 1) % MAX_PENDING;
}