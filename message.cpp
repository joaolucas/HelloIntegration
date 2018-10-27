#include "message.h"

Message::Message(QObject *parent) : QObject(parent),
    m_counter(0),
    m_message("How many clicks %1")

{

}

void Message::doMessageChange()
{
    m_counter++;
    emit messageChanged(m_message.arg(m_counter));
}
