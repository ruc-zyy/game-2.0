#include "bgm.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
bgm::bgm(QObject *parent)
    : QObject(parent)
    , m_backgroundMusic(NULL)
{
    QUrl backgroundMusicUrl = QUrl("qrc:/bgm.mp3");

        m_backgroundMusic = new QMediaPlayer(this);
        m_backgroundMusic->setVolume(10);
        QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();

        QMediaContent media(backgroundMusicUrl);
        backgroundMusicList->addMedia(media);
        backgroundMusicList->setCurrentIndex(0);
        // 设置背景音乐循环播放
        backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_backgroundMusic->setPlaylist(backgroundMusicList);

}
void bgm::startBGM(){

        m_backgroundMusic->play();
}
