#include "message.h"
#include <QDebug>

Message::Message(QObject *parent) : QObject(parent),
    m_counter(0),
    m_message("Start Now")

{

}

void Message::doMessageChange()
{
    setMessage("How many clicks %1");
//    m_counter++;
//    emit messageChanged(m_message.arg(m_counter));
}

QString Message::message() const
{
    return m_message;
}

void Message::setMessage(QString value)
{
    m_message = value.arg(m_counter);
    emit messageChanged();
}


int Message::sendMessageFromCpp(const QString value)
{
    qDebug() << "This is C++ speaking. I heard QML say:" << value;
    return m_counter;
}

