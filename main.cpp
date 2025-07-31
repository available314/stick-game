#include <QApplication>
#include "gamewindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(245, 245, 245));
    palette.setColor(QPalette::WindowText, Qt::black);
    app.setPalette(palette);

    GameWindow w;
    w.show();
    return app.exec();
}