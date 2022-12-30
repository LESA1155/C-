#include "mainwindow.h"
#include "addnets.h"
#include "redirectmsg.h"
#include <QApplication>

#define VERSION "1.1.0:33201"

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "--version")) {
            puts(VERSION);
            exit(0);
        }
    }


    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    //RedirectMsg rdm;
   //rdm.show();
    return app.exec();
}

/*
 * 2. Функционал Redirect Messges
 * 3. Функционал  AllocationUnits
 * 4. Функционал AddNets
 * 5. Оптимизировать showStack() , Через QMAP, как у Руслана
 * 6. Поработать над внешним стилем интерфейса
 * 7.
 */
