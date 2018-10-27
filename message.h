#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);

public slots:
    void doMessageChange();

signals:
    void messageChanged(QString value);

private:
    int m_counter;
    QString m_message;
};

#endif // MESSAGE_H
