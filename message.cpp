#include "message.h"

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
