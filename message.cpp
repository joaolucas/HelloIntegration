#include "message.h"
#include <iostream>

using std::cout;
using std::endl;

Message::Message(QObject *parent) : QObject(parent)
{

}

void Message::doMessageChange()
{
    cout << "We are in C++. Hooray!" << endl;
}
