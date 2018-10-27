# HelloIntegration

Este projeto tem com objetivo o apredizado inicial de QT. 


### QML signals para C++ Slots

Para que possamos realizar a comunicação entre o sinal do qml(view) para o c++(service) precisamos dos seguintes passos:

1. Criar o slot na classe .h
2. Implementar a definição do slot na class .cpp
3. Aplicar no context uma propriedade para o slot. 
4. Realizar chamada no arquivo qml

#### Implementação

- Crie uma classe c++ chamada Message
- Crie o slot no classe .h chamado doMessageChange();
```c++
public slots:
    void doMessageChange();   
```
- Crie uma implementação do doMessageChange() no aqruivo .cpp
```c++
void Message::doMessageChange()
{
    //Implementação..
}  
```
- Precisamos incluir no arquivo main o context e nossa nova class
```c++
#include <QQmlContext>
#include "message.h"
```
- Próximo passo é criar uma instancia da message e um ponteiro para o context antes de carregar o arquivo qml
```c++
 Message  my_msg;
 auto root_context = engine.rootContext();
```

- Agora precisamos criar uma propriedade no contexto com um nome e que aponte para nossa classe Message
```c++
root_context->setContextProperty("messageClass", &my_msg);
```

- Pronto! Agora só precisamos enviar o sinal com no click do botão no arquivo qml.

```qml
 Button{
            text : "Change Text" 
            onClicked: messageClass.doMessageChange()
        }
```


### C++ signals para QML Slots

Para que possamos realizar a comunicação entre o sinal do c++ para o qml precisamos dos seguintes passos:

1. Criar o signal na classe .h
2. Implementar a definição do slot no arquivo qml
3. Emitir a signal no arquivo cpp

#### Implementação

- Para inciar precisamos criar o sinal na nossa classe message.

```c++
signals:
    void messageChanged(QString value);
```
- No nosso exemplo iremos modificar a mensagem na parte visual e começa a contar quantas vezes o botão será apertado. Para isso precisaremos definir duas propriedades privadas na nossa classe Message.
```c++
private:
    int m_counter;
    QString m_message;
```
- Para exemplificar precisamos modificar a implementação do nosso método doMessageChange para 
```c++
void Message::doMessageChange()
{
    m_counter++;
    emit messageChanged(m_message.arg(m_counter));
}
```
- Quando criamos um sinal o framework do qt criar uma chamada de comunicação com o parão on + {nome do sinal}. No nosso caso ficou onMessageChanged. Agora precisamos cria uma conexão do qml com o signal do c++

```qml
   Connections{
        target: messageClass
        onMessageChanged: textId.text = value;
    }
```
