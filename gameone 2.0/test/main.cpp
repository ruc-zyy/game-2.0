#include "mainwindow.h"
#include <QApplication>
#include "form.h"
#include "bgm.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
Form f;
bgm *m_bgm=new bgm(&f);
m_bgm->startBGM();
f.show();

    return a.exec();
}
