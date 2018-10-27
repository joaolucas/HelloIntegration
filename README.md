# HelloIntegration

Este projeto tem com objetivo o apredizado inicial de QT. 


### QML signals para C++ Slots

Para que possamos realizar a comunicação entre o sinal do qml(view) para o c++(service) precisamos dos seguintes passos:

1. Criar o slot na classe .h
2. Implementar a definição do slot na class .cpp
3. Aplicar no context uma propriedade para o slot. 
4. Realizar chamada no arquivo qml

#### Ponto 1

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
