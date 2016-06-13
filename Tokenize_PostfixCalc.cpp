#include <QCoreApplication>
#include <QVector>
#include <QDebug>

QVector<QString> Tokenize (QString expression)
{
    QVector<QString> TokenList;
    int i = 0;
    while(i < expression.length())
    {
        if(expression[i].isDigit())
        {
            QString temp;
            temp.append(expression[i]);
            while(expression[i+1].isDigit() || expression[i+1]=='.')
            {
                temp.append(expression[i+1]);
                i++;
            }
            //Agregar error de exclusion
            TokenList.append(temp);
            i++;
        }
        else if(expression[i].isLetter())
        {
            QString temp;
            temp.append(expression[i]);
            while(expression[i+1].isLetter())
            {
                temp.append(expression[i+1]);
                i++;
            }
            TokenList.append(temp);
            i++;
        }
        else if (!expression[i].isSpace())
        {
            QString temp;
            temp.append(expression[i]);
            TokenList.append(temp);
            i++;
        }
        else
            i++;
    }
    return TokenList;
}

typedef double calc;

QMap<QString, int> argnumberOperator = {
    {"+", 2},
    {"-", 2},
    {"*", 2},
    {"/", 2},
    {"^", 2},
    {"sin", 1},
    {"cos", 1},
    {"tan", 1},
    {"ctg", 1},
    {"sec", 1},
    {"csc", 1}
};

QMap<QString, calc> Operation = {
    {"sin", },
    {"cos", },
    {"tan", },
    {"ctg", },
    {"sec", },
    {"csc", },
    {"+", },
    {"-", },
    {"*", },
    {"/", },
    {"^", }
};

calc PostfixCalculate (QVector<QString> PostfixTokens)
{
    QVector<QString> tempStack;
    while (!PostfixTokens.empty())
    {
        std::for_each (PostfixTokens.begin(), PostfixTokens.end(), [](QString Token)
        {
            QRegExp numToken("\\d*");
            if (numToken.exactMatch(Token))
                tempStack.push_front(Token);
            else if (PostfixTokens.length()>=argnumberOperator[Token])
            {
                //Sacar los n valores de TempStack
                //Evaluar la operacion
                //Push el resultado
            }
        })
    }
    //Si solo hay un valor en la pila, ese es el resultado
    //Si hay mas de un valor, el usuario ha ingresado muchos valores
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QString> test = Tokenize("sin (3.15 +15*5/10    ) /10  ^ 5");
    QVector<QString>::iterator it;
    for (it=test.begin(); it<test.end(); it++)
        qDebug() << *it;
    return a.exec();
}
