#include <QCoreApplication>
#include <QVector>
#include <QDebug>
#include <QRegExp>
#include <math.h>

typedef QVector<QString> tokenlist;

tokenlist Tokenize (QString expression)
{
    tokenlist TokenList;
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
            if (temp == "e")
                temp = "2.71828182";
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

calc Addition (tokenlist tokens)
{
    calc result = 0;
    for (int i=0; i<tokens.length(); i++)
    {
        result += tokens[i].toDouble();
    }
    return result;
}

calc Substraction (tokenlist tokens)
{
    calc result = tokens.first().toDouble();
    for (int i=1; i<tokens.length(); i++)
    {
        result -= tokens[i].toDouble();
    }
    return result;
}

calc Multiplication (tokenlist tokens)
{
    calc result = 1;
    for (int i=0; i<tokens.length(); i++)
    {
        result *= tokens[i].toDouble();
    }
    return result;
}

calc Division (tokenlist tokens)
{
    calc result = tokens.first().toDouble();
    for (int i=1; i<tokens.length(); i++)
    {
        result /= tokens[i].toDouble();
    }
    return result;
}

calc Exponentiation (tokenlist tokens)
{
    return pow(tokens.first().toDouble(), tokens.last().toDouble());
}

calc Sine (tokenlist tokens)
{
    return sin(tokens.first().toDouble());
}

calc Cosine (tokenlist tokens)
{
    return cos(tokens.first().toDouble());
}

calc Tangent (tokenlist tokens)
{
    return tan(tokens.first().toDouble());
}

calc Cotangent (tokenlist tokens)
{
    return 1/tan(tokens.first().toDouble());
}

calc Secant (tokenlist tokens)
{
    return 1/cos(tokens.first().toDouble());
}

calc Cosecant (tokenlist tokens)
{
    return 1/sin(tokens.first().toDouble());
}

calc Log10 (tokenlist tokens)
{
    return log10(tokens.first().toDouble());
}

calc LogE (tokenlist tokens)
{
    return log(tokens.first().toDouble());
}

calc Log2 (tokenlist tokens)
{
    return log2(tokens.first().toDouble());
}

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
    {"csc", 1},
    {"log", 1},
    {"ln", 1},
    {"lg", 1}
};

typedef calc (*operate)(tokenlist);

QMap<QString, operate> Operation = {
    {"+", Addition},
    {"-", Substraction},
    {"*", Multiplication},
    {"/", Division},
    {"^", Exponentiation},
    {"sin", Sine},
    {"cos", Cosine},
    {"tan", Tangent},
    {"ctg", Cotangent},
    {"sec", Secant},
    {"csc", Cosecant},
    {"log", Log10},
    {"ln", LogE},
    {"lg", Log2}
};

calc PostfixCalculate (tokenlist PostfixTokens)
{
    tokenlist tempStack;
    std::for_each (PostfixTokens.begin(), PostfixTokens.end(), [&PostfixTokens, &tempStack](QString Token)
    {
        QRegExp numToken("\\d+\\.?\\d*");
        if (numToken.exactMatch(Token))
            tempStack.push_front(Token);
        else if (tempStack.length() >= argnumberOperator[Token])
        {
            tokenlist operands;
            for (int i=0; i<argnumberOperator[Token]; i++)
            {
                operands.push_front(tempStack.first());
                tempStack.pop_front();
            }
            calc tempValue = (*(Operation[Token]))(operands);
            tempStack.push_front(QString::number(tempValue));
        }
        //else:  Error: El usuario ha ingresado insuficientes valores
    });
    if (tempStack.length() == 1)
        return tempStack.first().toDouble();
    else
        return 0; //El usuario ha ingresado muchos valores. Agregar error.
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tokenlist test = Tokenize ("5 1 2 + 4 * + 3 - ln"); // ln (5 + ((1 + 2) * 4) − 3)
    QVector<QString>::iterator it;
    for (it=test.begin(); it<test.end(); it++)
        qDebug() << *it;
    calc result = PostfixCalculate(test);
    qDebug() << result;
    return a.exec();
}
