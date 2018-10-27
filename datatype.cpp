#include "datatype.h"
#include <QColor>
#include <QVariant>
DataType::DataType(QObject *parent) : QObject(parent)
{

}

void DataType::logVariantList(QObject *root)
{
    QColor color = Qt::green;
    QVariantList my_list;
    my_list << 3.1415 << 30 << color << "lucas";

    QMetaObject::invokeMethod(root, "logList", Q_ARG(QVariant, QVariant::fromValue(my_list)));
}

void DataType::logVariantMap(QObject *root)
{

}
