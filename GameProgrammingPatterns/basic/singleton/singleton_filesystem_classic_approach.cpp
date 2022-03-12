class FileSystem { 
public:
    static FileSystem& instance();

    virtual ~FileSystem() {}
    virtual char* readFile(char* path) = 0;
    virtual void writeFile(char* path, char* contents) = 0;
private:
    FileSystem() {}
};

class PS3FileSystem : public FileSystem { 
public:
    virtual char* readFile(char* path) {
        // Use Sony file IO API...
    }
    virtual void writeFile(char* path, char* contents) {
        // Use Sony file IO API...
    }
};
class WiiFileSystem : public FileSystem { 
public:
    virtual char* readFile(char* path) {
        // Use Nintendo file IO API...
    }
    virtual void writeFile(char* path, char* contents) {
        // Use Nintendo file IO API...
    }
};

FileSystem& FileSystem::instance()
{
    #if PLATFORM == PLAYSTATION3
        static FileSystem *instance = new PS3FileSystem();
    #elif PLATFORM == WII
        static FileSystem *instance = new WiiFileSystem();
    #endif
    return *instance;
}