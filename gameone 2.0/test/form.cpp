#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "QPainter"
#include <QMediaPlayer>
#include "bgm.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;


}



void Form::on_pushButton_clicked()
{
    MainWindow *w=new MainWindow();
    w->show();
}
void Form::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/image/startpic.bmp"));}
