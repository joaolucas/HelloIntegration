#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
public:
    explicit Message(QObject *parent = nullptr);

    QString message() const;
    void setMessage(QString value);

    Q_INVOKABLE int sendMessageFromCpp(const QString value);


public slots:
    void doMessageChange();

signals:
    void messageChanged();

private:
    int m_counter;
    QString m_message;
};

#endif // MESSAGE_H
