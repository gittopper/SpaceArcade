//
// Created by stanislav on 21.03.2025.
//

#ifndef ANDROIDSTUDIO_ISOUNDPLAYER_H
#define ANDROIDSTUDIO_ISOUNDPLAYER_H

#include <string>

class ISoundPlayer {
public:
    virtual void play(const std::string& sound_file_name) = 0;
};


#endif //ANDROIDSTUDIO_ISOUNDPLAYER_H
