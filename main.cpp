#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "message.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Message  my_msg;
    auto root_context = engine.rootContext();
    root_context->setContextProperty("messageClass", &my_msg);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();

}
