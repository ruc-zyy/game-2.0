#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bullet.h"
#include "enemy.h"
#include <QMainWindow>
#include <towerposition.h>
#include <tower.h>
#include <QPainter>
#include <QMovie>
#include <waypoint.h>
#include <QTimer>
#include "bgm.h"
class Enemy;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    bool canBuyTower() const;
    void drawtower();
    void addBullet(Bullet *bullet);
    void getHpDamage(int damege=1);
    void removedBullet(Bullet *bullet);
    void doGameOver();
    void awardGold(int num);
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void removeTower(Tower *tower);
    void addWayPoints();
    void removedEnemy(Enemy *enemy);
    bool loadWave();
    int m_playerGold=1000;
    int numoftower=0;
    int numofwolf=0;

    bgm *m_bgm;

    QLabel *enemylabel[100]={new QLabel(this)};
    QList<QLabel *> e;
    QLabel *towerlabel[50]={new QLabel(this)};
    QList<QLabel *> t;
    QMovie *pic[50]={new QMovie(":/image/tower4.gif")};
    QMovie *pic2[50]={new QMovie(":/image/lv2tower.gif")};
    QMovie *dis[50];
    QMovie *epic[100]={new QMovie(":/image/wolf.gif")};
    QMovie *wolfpic[100]={new QMovie(":/image/wolfking.gif")};
    QMovie *dragonpic[100]={new QMovie(":/image/dragon.gif")};
    QList<QMovie *> ep;
    QList<WayPoint *> m_wayPointsList;
    QList<Enemy *> m_enemyList;
    QList<Enemy *> enemyList() const;
    QList<Bullet *>			m_bulletList;

    QTimer *timer = new QTimer(this);


protected:
 void paintEvent(QPaintEvent *);
protected slots:
 void updateMap();
 void gamestart();
 void stopdis();
private slots:
 void on_pushButton_clicked();

 void on_pushButton_2_clicked();

 void on_pushButton_3_clicked();

 void on_pushButton_4_clicked();

 void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    void loadTowerPositions();

    int m_waves=0;
    int m_playerHp=10;
    bool m_gameEnded=false;
    bool m_gameWin=false;
    bool deletto=false;
    bool levelup=false;
    int towertype=0;
    int num2=0;
    QList<TowerPosition> m_towerPositionsList;
    QList<Tower *> m_towersList;
    QLabel *disappear=new QLabel(this);

};

#endif // MAINWINDOW_H
