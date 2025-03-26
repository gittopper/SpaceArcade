#include "soundplayer.h"

#include <QAudioOutput>
#include <QApplication>

SoundPlayer::SoundPlayer(){
    player_ = std::make_shared<QMediaPlayer>();
    auto output = new QAudioOutput(player_.get());
    output->setVolume(20);
    player_->setAudioOutput(output);
}

void SoundPlayer::play(const std::string& sound_file_name) {
    player_->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + QString::fromStdString(std::string("/assets/") + sound_file_name)));
    player_->play();
}
