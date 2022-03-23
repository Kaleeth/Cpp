
#define VERY_LOUD_BANG 1

class Audio { 
public:
    virtual ~Audio() {}
    virtual void playSound(int soundID) = 0;
    virtual void stopSound(int soundID) = 0;
    virtual void stopAllSounds() = 0;
    
};

class ConsoleAudio : public Audio { 
public:
    virtual void playSound(int soundID) {
        // Play sound using console audio api...
    }
    virtual void stopSound(int soundID) {
        // Stop sound using console audio api...
    }
    virtual void stopAllSounds() {
        // Stop all sounds using console audio api...
    }
};

class NullAudio: public Audio {
public:
    virtual void playSound(int soundID) { /* Do nothing. */ }
    virtual void stopSound(int soundID) { /* Do nothing. */ }
    virtual void stopAllSounds() { /* Do nothing. */ }
};

// example of Decorator for a Service 
// (here logging decorator for audio service)
class LoggedAudio : public Audio {
public:
    LoggedAudio(Audio &wrapped)
    : wrapped_(wrapped)
    {}

    virtual void playSound(int soundID) {
        log("play sound");
        wrapped_.playSound(soundID);
    }
    virtual void stopSound(int soundID) {
        log("stop sound");
        wrapped_.stopSound(soundID);
    }
    virtual void stopAllSounds() {
        log("stop all sounds");
        wrapped_.stopAllSounds();
    }

private:
    void log(const char* message) {
        // Code to log message...
    }
    Audio &wrapped_;
};

// function called by user to enable logging audio service
void enableAudioLogging() {
    // Decorate the existing service.
    Audio *service = new LoggedAudio(Locator::getAudio());
    // Swap it in.
    Locator::provide(service);
}

class Locator { 
public:
    static void initialize() { service_ = &nullService; }

    static Audio& getAudio() { return *service_; }
    
    static void provide(Audio* service) {
        if (service == nullptr) {
            // Revert to null service
            service_ = &nullService;
        }
        else {
            service_ = service;
        }
    }

private:
    static Audio* service_;
    static NullAudio nullService;

    // binding services at compile time
    // #if DEBUG
    // static DebugAudio service_;
    // #else
    // static ReleaseAudio service_;
    // #endif
};

int main() {
    ConsoleAudio* audio = new ConsoleAudio();
    Locator::provide(audio);
    // ...
    Audio& audio = Locator::getAudio();
    audio->playSound(VERY_LOUD_BANG);
}