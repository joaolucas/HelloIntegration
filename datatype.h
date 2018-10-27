#ifndef DATATYPE_H
#define DATATYPE_H

#include <QObject>

class DataType : public QObject
{
    Q_OBJECT
public:
    explicit DataType(QObject *parent = nullptr);    
    void logVariantList(QObject *root);
    void logVariantMap(QObject *root);

signals:

public slots:
};

#endif // DATATYPE_H
