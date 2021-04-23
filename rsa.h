#ifndef RSA_H
#define RSA_H
#include "BigInt.hpp"

#include <algorithm>
#include <ctime>

#include <QVector>
#include <QString>

class RSA
{
private:
    BigInt P;
    BigInt Q;
    BigInt N;
    BigInt d;
    BigInt s;
    BigInt e;

    BigInt generate_s(BigInt d);
    BigInt generate_e(BigInt d, BigInt s);
    BigInt sundaram(BigInt n);
public:
    RSA();
    ~RSA();

    void restart();
    QString option();

    BigInt get_N();
    BigInt get_s();

    QVector<BigInt> coding(QString text, BigInt N, BigInt s);
    QString decoding(QVector<BigInt> code);
};

#endif // RSA_H
