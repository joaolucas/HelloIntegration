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

### Utilizando Q_PROPERTY

Esta macro é usada para declarar propriedades em classes que herdam o QObject.As propriedades se comportam como membros de dados de classe, mas possuem recursos adicionais acessíveis por meio do Meta-Object System.

#### Implementação

- Para utilizar o @Q_PROPERTY coloque na classe Message a definição do property.

```c++
Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
```

- Defina os metodos get e set com definido no property

```c++
    QString message() const;
    void setMessage(const QString &message);
```

- Agora que temos uma propriedade definida não preciraremos mais ter o paramento no método messageChanged.

```c++
 void messageChanged();
```

- Vamos modificar a implementação do arquivo .cpp para a classe Message. Colocaremos o metodo get e set e iremos refatorar os sinal messageChanged()

```c++
void Message::doMessageChange()
{
    setMessage("How many clicks %1");
//    m_counter++;
//    emit messageChanged(m_message.arg(m_counter));
}

void Message::setMessage(QString value)
{
    m_message = value.arg(++m_counter);
    emit messageChanged();
}
```

- Como temos a propriedade definida e configurada não precisaremos da definicao do Connection dentro do qml. Modificaremos o QML para que o texto seja atualizado pelo property.

```qml
 //    Connections{
//        target: messageClass
//        onMessageChanged: textId.text = value;
//    }

    Column{
        Text {
            id: textId
            //text: qsTr("Hello New World")
            text: messageClass.message
        }
```

### Utilizando Q_INVOKABLE (Two way comunication)
Aplique essa macro às declarações de funções-membro para permitir que elas sejam invocadas por meio do sistema de two way comunication.

#### Implementação

- Para iniciar definiremos um método sendMessageFromCpp na class Message utilizando a declaração Q_INVOKABLE

```c++
Q_INVOKABLE int sendMessageFromCpp(const QString value);
```
- Agora faremos um implementação do metodo no arquivo cpp que receberá um valor do qml e retornará um valor que o qml.
```c++
int Message::sendMessageFromCpp(const QString value)
{
    qDebug() << "This is C++ speaking. I heard  QML say: " <<value;
    return m_counter;
}
```

- Para nosso exemplo criaremos um outro botão na tela do qml chamando o metodo sendMessageFromCpp e implementando alguma lógica com o retorno. 
```qml
 Button{
            text : "Two way"
            onClicked:{
                var result = messageClass.sendMessageFromCpp("lucas")
                print("QML Received " + result);
            }
        }
```

### QVariantList e  QVariantMap

Nessa exemplo iremos trabalha com duas estutura de lista para o qt. Porém temos que entender o QVariant.
A classe QVariant atua como uma união para os tipos de dados mais comuns do Qt.
O QVariant possui uma interface rica para conversão de dados e verificação de validade.


#### Implementação

- Para nosso exemplo criaremos um comunicação (two way) porém utilizando javaScript no código qml. Assim fica mais legal :)
- Primeiro definiremos dos método de log para QVariantList e QVariantMap em uma nova classe chamada DataType

```c++
public:
    explicit DataType(QObject *parent = 0);
    void logVariantList(QObject* root);
    void logVariantMap(QObject* root);
```

- Agora implementaremos nosso primeiro método QVariantList

```c++
void DataType::logVariantList(QObject *root)
{
    QColor color = Qt::green;
    QVariantList my_list;
    my_list << 3.1415 << 30 << color << "lucas";
    QMetaObject::invokeMethod(root, "logArray",
                              Q_ARG(QVariant,
                                    QVariant::fromValue(my_list)));
}
```

- Para que nosso exemplo funcione corretamento não podemos utlizar javasscript com interação do context. Iremos criar um root objet na nossa class main e passa como paramento para o método logVariant list do nosso datatype.
```c++
 auto root_object = engine.rootObjects().first();

    DataTypes my_dts;
    my_dts.logVariantList(root_object);
```

- Criaremos duas funções javaScript no nosso arquivo qml para executar a lógica na view. 
```javascript
  function logger(element)
    {
        print("Array element:" + element)
    }
    
    function logArray(anArray)
    {
        anArray.forEach(logger);
    }
    ```
    **Lembrando que o nome da função javascrit deve ser igual à definida na invocação de método.

