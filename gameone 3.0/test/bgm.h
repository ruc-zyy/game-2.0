#ifndef BGM_H
#define BGM_H

#include <QObject>

class QMediaPlayer;
class bgm:public QObject
{
public:
    explicit bgm(QObject *parent = 0);
    void startBGM();
private:
    QMediaPlayer *m_backgroundMusic;
};

#endif // BGM_H
