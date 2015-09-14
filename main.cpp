#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "BoardQObjectAbstraction.h"
int main(int argc, char *argv[])
{
    BoardQObjectAbstraction * bqoa = new BoardQObjectAbstraction();
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("MainBoard", bqoa);
    return app.exec();
}
