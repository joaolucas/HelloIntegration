#include "datatype.h"
#include <QColor>
#include <QVariant>
#include <QDate>
DataType::DataType(QObject *parent) : QObject(parent)
{

}

void DataType::logVariantList(QObject *root)
{
    QVariantList my_list;

    QColor color = Qt::green;
    my_list << 3.1415 << 30 << color << "lucas";

    QMetaObject::invokeMethod(root, "logList", Q_ARG(QVariant, QVariant::fromValue(my_list)));
}

void DataType::logVariantMap(QObject *root)
{

    QVariantMap my_map;
    my_map.insert("newLanguage", "c++");
    my_map.insert("StdReleased", QDate(2018,8,12));
    my_map.insert("oldLanguage", "QML");
    my_map.insert("QMLreleased", QDate(2011, 3, 4));

    QMetaObject::invokeMethod(root, "logMap", Q_ARG(QVariant, QVariant::fromValue(my_map)));


}
