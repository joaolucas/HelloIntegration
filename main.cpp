#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "message.h"
#include "datatype.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Message  my_msg;
    auto root_context = engine.rootContext();
    root_context->setContextProperty("messageClass", &my_msg);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    auto root_objet = engine.rootObjects().first();
    DataType my_data;
    my_data.logVariantList(root_objet);


    return app.exec();

}
