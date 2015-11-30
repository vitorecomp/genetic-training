#ifndef IOMananger_H
#define IOMananger_H

class Configs{
public:
    Configs();

    void openFile(char*);
    void setConfigs();
};


namespace io{
    extern Configs configs;
}

#endif
