#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemy.h"
#include "wolfking.h"
#include <QPainter>
#include <towerposition.h>
#include <QMouseEvent>
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include "utility.h"
#include<windows.h>
#include "bgm.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)

{
    ui->setupUi(this);


for(int i=0;i<=49;i++){
    towerlabel[i]=new QLabel(this);

    pic2[i]=new QMovie(":/image/lv2tower.gif");
    dis[i]=new QMovie(":/image/disappear.gif");
    pic[i]=new QMovie(":/image/tower4.gif");

}
for(int i=0;i<=99;i++){
    enemylabel[i]=new QLabel(this);
    epic[i]=new QMovie(":/image/wolf.gif");
    wolfpic[i]=new QMovie(":/image/wolfking.gif");
    dragonpic[i]=new QMovie(":/image/dragon.gif");

}
loadTowerPositions();
addWayPoints();

connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
timer->start(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/image/map1.png"));

    for(int i=0;i<m_towerPositionsList.size();i++){
        m_towerPositionsList[i].draw(&painter);

    }

drawHP(&painter);
drawWave(&painter);
drawPlayerGold(&painter);
foreach(Tower *tower,m_towersList){
tower->draw(towerlabel,pic[tower->no],&painter);
}

foreach(Enemy *enemy,m_enemyList){
    enemy->draw(&painter,enemylabel);
}

foreach(Bullet *bullet,m_bulletList){
    bullet->draw(&painter);
}


if (m_gameEnded || m_gameWin)

{
    if(m_gameEnded) {
       painter.drawPixmap(QPoint(250,250),QPixmap(":/image/defeat.png"));
    }
else{

 painter.drawPixmap(QPoint(250,250),QPixmap(":/image/victory.png"));
}

    return;

}

}

void MainWindow::loadTowerPositions(){
    QPoint pos[] =	{

        QPoint(320, 100),
        QPoint(470, 100),
        QPoint(550, 100),
        QPoint(160, 250),
        QPoint(320, 250),
        QPoint(480, 250),
        QPoint(700, 250),
        QPoint(170, 390),

        QPoint(550, 390),
        QPoint(320, 480),
        QPoint(400, 550),
        QPoint(620, 550),
        QPoint(170, 620),

                    };
    int len	= sizeof(pos) / sizeof(pos[0]);
    for (int i = 0; i < len; ++i) m_towerPositionsList.push_back(pos[i]);

}

void MainWindow::mousePressEvent(QMouseEvent *event)

{
    if(!deletto&&!levelup){
if(towertype==0) return;
    QPoint pressPos=event->pos();

    auto it = m_towerPositionsList.begin();

    while (it != m_towerPositionsList.end())

    {

        if (canBuyTower() && it->containPoint(pressPos)&&!it->t_hasTower)

        {


numoftower=numoftower+1;
Tower *tower=new Tower(towertype,it->centerPos(),numoftower,this);
            m_towersList.push_back(tower);
m_playerGold-=tower->m_cost;
it->setHasTower(tower);
towertype=0;
            update();

            break;

        }



        ++it;

    }
}
    if(deletto&&!levelup){
        QPoint pressPos=event->pos();
        auto it = m_towerPositionsList.begin();

        while (it != m_towerPositionsList.end())
        {

            if (it->containPoint(pressPos) && it->hasTower())

            {
removeTower(it->m_tower);
               it->t_hasTower=false;
               deletto=false;
               it->m_tower=NULL;
               m_playerGold+=30;
               break;
            }
            ++it;
        }

    }
    if(levelup&&!deletto){
        if(m_playerGold>=100) {
        QPoint pressPos=event->pos();
        auto it = m_towerPositionsList.begin();

        while (it != m_towerPositionsList.end())
        {

            if (it->containPoint(pressPos) && it->hasTower())

            {
it->m_tower->up();
levelup=false;
m_playerGold-=100;
               break;
            }
            ++it;
        }
        }
    }

    if(levelup&&deletto){}
    deletto=false;
    levelup=false;
    towertype=0;
}



bool MainWindow::canBuyTower() const

{

    if(m_playerGold>=60){
        return true;
    }
    else {
        return false;
    }
}

void MainWindow::addWayPoints()

{

    WayPoint *wayPoint1 = new WayPoint(QPoint(120, 330));

    m_wayPointsList.push_back(wayPoint1);



    WayPoint *wayPoint2 = new WayPoint(QPoint(270, 330));

    m_wayPointsList.push_back(wayPoint2);

    wayPoint2->setNextWayPoint(wayPoint1);



    WayPoint *wayPoint3 = new WayPoint(QPoint(270, 640));

    m_wayPointsList.push_back(wayPoint3);

    wayPoint3->setNextWayPoint(wayPoint2);



    WayPoint *wayPoint4 = new WayPoint(QPoint(730, 640));

    m_wayPointsList.push_back(wayPoint4);

    wayPoint4->setNextWayPoint(wayPoint3);



    WayPoint *wayPoint5 = new WayPoint(QPoint(730, 495));

    m_wayPointsList.push_back(wayPoint5);

    wayPoint5->setNextWayPoint(wayPoint4);



    WayPoint *wayPoint6 = new WayPoint(QPoint(433, 495));

    m_wayPointsList.push_back(wayPoint6);

    wayPoint6->setNextWayPoint(wayPoint5);



    WayPoint *wayPoint7 = new WayPoint(QPoint(433, 330));

    m_wayPointsList.push_back(wayPoint7);

    wayPoint7->setNextWayPoint(wayPoint6);


    WayPoint *wayPoint8 = new WayPoint(QPoint(650, 330));

    m_wayPointsList.push_back(wayPoint8);

    wayPoint8->setNextWayPoint(wayPoint7);


    WayPoint *wayPoint9 = new WayPoint(QPoint(650, 185));

    m_wayPointsList.push_back(wayPoint9);

    wayPoint9->setNextWayPoint(wayPoint8);


    WayPoint *wayPoint10 = new WayPoint(QPoint(150, 185));

    m_wayPointsList.push_back(wayPoint10);

    wayPoint10->setNextWayPoint(wayPoint9);
}


bool MainWindow::loadWave()

{

    if (m_waves >= 5)

        return false;

    WayPoint *startWayPoint = m_wayPointsList.back(); // 这里是个逆序的，尾部才是其实节点
if(m_waves==0){
    int enemyStartInterval[] = { 100, 1000, 2500, 3500, 5000, 6000, 7000 };
    for (int i = 0; i < 7; ++i)
    {
        numofwolf++;
        int t_type=1;
        if(i==6) t_type=2;
        Enemy *enemy = new Enemy(numofwolf,t_type,startWayPoint->pos(),startWayPoint->nextWayPoint(), this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
}
else if(m_waves==1){
    int enemyStartInterval[] = { 100, 1000, 2500, 3500, 5000, 6000,7000};
    for (int i = 0; i < 6; ++i)
    {
        numofwolf++;
        int t_type=1;
        if(i>=5||i==0) t_type=2;
        Enemy *enemy = new Enemy(numofwolf,t_type,startWayPoint->pos(),startWayPoint->nextWayPoint(), this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
}
else if(m_waves==2){
    int enemyStartInterval[] = { 100, 1000, 2500, 3500, 5000, 6000,7000};
    for (int i = 0; i < 6; ++i)
    {
        numofwolf++;
        int t_type=1;
        if(i==0) t_type=3;
        Enemy *enemy = new Enemy(numofwolf,t_type,startWayPoint->pos(),startWayPoint->nextWayPoint(), this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
}
else if(m_waves==3){
    int enemyStartInterval[] = { 100, 1000, 2500, 3500, 5000, 6000,7000};
    for (int i = 0; i < 6; ++i)
    {
        numofwolf++;
        int t_type=1;
        if(i==2) t_type=3;
        if(i==6) t_type=2;
        Enemy *enemy = new Enemy(numofwolf,t_type,startWayPoint->pos(),startWayPoint->nextWayPoint(), this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
}
else if(m_waves==4){
    int enemyStartInterval[] = { 100, 1000, 2500, 3500, 5000, 6000,7000};
    for (int i = 0; i < 6; ++i)
    {
        numofwolf++;
        int t_type=1;
        if(i==2||i==4) t_type=3;
        if(i==6||i==0) t_type=2;
        Enemy *enemy = new Enemy(numofwolf,t_type,startWayPoint->pos(),startWayPoint->nextWayPoint(), this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
}
    return true;

}


void MainWindow::updateMap()

{

    foreach (Enemy *enemy, m_enemyList)

        enemy->move();

    foreach (Tower *tower, m_towersList)

    {
        if(tower->type==1)tower->checkEnemyInRange();

    }
    update();

}


void MainWindow::getHpDamage(int damage/* = 1*/)

{



    m_playerHp -= damage;

    if (m_playerHp <= 0)

        doGameOver();

}



void MainWindow::doGameOver()

{

    if (!m_gameEnded)

    {

        m_gameEnded = true;

        // 此处应该切换场景到结束场景

        // 暂时以打印替代,见paintEvent处理

    }

}


void MainWindow::removedEnemy(Enemy *enemy)

{

    Q_ASSERT(enemy);
    enemylabel[enemy->no]=NULL;
       delete enemylabel[enemy->no];
   if(enemy->type==1) delete epic[enemy->no];
   if(enemy->type==2) delete wolfpic[enemy->no];
   if(enemy->type==3) delete dragonpic[enemy->no];
    m_enemyList.removeOne(enemy);

    if(enemy->type==2){
        for(int k=0;k<=2;k++){
            numofwolf++;
            Enemy *awolf = new Enemy(numofwolf,1,enemy->m_pos-QPoint(50,50)+QPoint(50*k,50*k),enemy->m_destinationWayPoint, this);

            m_enemyList.push_back(awolf);

            awolf->doActivate();
        }
    }
    if(enemy->type==3){

        auto it = m_towerPositionsList.begin();

        while (it != m_towerPositionsList.end()){
            if(collisionWithCircle(enemy->m_pos,200,it->t_pos,1)&&it->t_hasTower){

                 removeTower(it->m_tower);
                 it->t_hasTower=false;
                 it->m_tower=NULL;
                 disappear->setGeometry(it->t_pos.x()-10,it->t_pos.y()-40,90,100);
                 disappear->setScaledContents(true);
                 disappear->setMovie(dis[num2]);

                               break;
            }
            ++it;
        }

        dis[num2]->start();
 QTimer::singleShot(1000,this, SLOT(stopdis()));
    }
    delete enemy;



    if (m_enemyList.empty())

    {

        ++m_waves; // 当前波数加1

        // 继续读取下一波

        if (!loadWave())

        {

            // 当没有下一波时，这里表示游戏胜利

            // 设置游戏胜利标志为true

           m_gameWin=true;

            // 游戏胜利转到游戏胜利场景

            // 这里暂时以打印处理

        }

    }

}
void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}
void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}
QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::awardGold(int num){
    m_playerGold+=num;
    update();
}


void MainWindow::drawWave(QPainter *painter)

{

    painter->setPen(QPen(Qt::red,200));

    painter->drawText(QRect(310, 15, 200, 50), QString("WAVE : %1").arg(m_waves + 1));

}



void MainWindow::drawHP(QPainter *painter)

{

    painter->setPen(QPen(Qt::red,200));

    painter->drawText(QRect(25, 15, 200, 50), QString("HP : %1").arg(m_playerHp));

}



void MainWindow::drawPlayerGold(QPainter *painter)

{

    painter->setPen(QPen(Qt::red,200));

    painter->drawText(QRect(170, 15, 400, 50), QString("GOLD : %1").arg(m_playerGold));

}

void MainWindow::gamestart(){
    loadWave();
}

void MainWindow::on_pushButton_clicked()
{
    towertype=2;
}

void MainWindow::on_pushButton_2_clicked()
{
    towertype=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    deletto=true;

}

void MainWindow::removeTower(Tower *tower){

    Q_ASSERT(tower);
    m_towersList.removeOne(tower);
    if(tower->type==1){
        if(tower->m_chooseEnemy!=NULL){
            tower->m_chooseEnemy->m_attackedTowersList.removeOne(tower);
        }
        towerlabel[tower->no]=NULL;
        delete towerlabel[tower->no];
        delete pic[tower->no];
        delete pic2[tower->no];
    }
    delete tower;


}

void MainWindow::on_pushButton_4_clicked()
{
    levelup=true;
}

void MainWindow::on_pushButton_5_clicked()
{
    gamestart();
}
void MainWindow::stopdis(){

    dis[num2]->stop();
    delete dis[num2];

    num2++;

}
