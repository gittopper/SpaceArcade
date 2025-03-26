#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H


#include <game/isoundplayer.h>
#include <QMediaPlayer>

class SoundPlayer: public ISoundPlayer {
public:
    SoundPlayer();
    void play(const std::string& sound_file_name) override;
private:
    std::shared_ptr<QMediaPlayer> player_;
};

#endif // SOUNDPLAYER_H
