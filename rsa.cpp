#include "rsa.h"

RSA::RSA()
{
    restart();
}

RSA::~RSA()
{

}

BigInt RSA::generate_s(BigInt d)
{
    BigInt s = 2;
    do
    {
        s += 1;
    }while (std::__gcd(d, s) !=1 && s < d);

    return s;
}

BigInt RSA::generate_e(BigInt d, BigInt s)
{
    BigInt e = 0;
    do
    {
        e++;
    }while ((e * s) % d != 1);

    return e;
}



BigInt RSA::sundaram(BigInt n)
{
    QVector<BigInt> a;
    BigInt i, j, k;
    a.resize(n.to_long_long());
    for(i = 1; i * 3 + 1 < n; i++)
    {
        for(j = 1; (k = i + j + i * j * 2) < n && j <= i; j++) a[k.to_long_long()] = 1;
    }
    for(i = n-1; i >= 1; i--)
    {
        if(a[i.to_long_long()] == 0)
        {
            return (i * 2 + 1);
        }
    }
    return 3;
}

void RSA::restart()
{
    srand( (unsigned) time( NULL ) );
    int p = rand()%100+50; int q = rand()%100+50;
    this->P =sundaram(p); this->Q = sundaram(q);

    this->N = this->P * this->Q;
    this->d = (this->P - 1) * (this->Q - 1);
    this->s = this->generate_s(this->d);
    this->e = this->generate_e(this->d, this->s);
}

QString RSA::option()
{
    QString s = "";

    s = s + "P = " + QString::fromStdString(this->P.to_string()) + "\nQ = " + QString::fromStdString(this->Q.to_string()) + "\n";
    s = s + "N = " + QString::fromStdString(this->N.to_string()) + "\n";
    s = s + "d = " + QString::fromStdString(this->d.to_string()) + "\n";
    s = s + "s = " + QString::fromStdString(this->s.to_string()) + "\n";
    s = s + "e = " + QString::fromStdString(this->e.to_string());

    return s;
}

BigInt RSA::get_N()
{
    return this->N;
}

BigInt RSA::get_s()
{
    return this->s;
}

BigInt abss(const BigInt& num) {
    return num < 0 ? -num : num;
}


BigInt powe(const BigInt& base, int exp) {

    BigInt result = base, result_odd = 1;
    while (exp > 1) {
        if (exp % 2)
            result_odd *= result;
        result *= result;
        exp /= 2;
    }

    return result * result_odd;
}

BigInt powe(const long long& base, int exp) {
    return powe(BigInt(base), exp);
}

BigInt powe(const std::string& base, int exp) {
    return powe(BigInt(base), exp);

}


QVector<BigInt> RSA::coding(QString text, BigInt N, BigInt s)
{
    QVector<BigInt> code;
    BigInt n, powe;
    long long t;
    for(auto i:text)
    {
        n = 1;
        powe = i.unicode();
        t = s.to_int();
        while(t--)
        {
            n = n * powe;
            n = n % N;
        }
        code.push_back(n);
    }

    return code;
}

QString RSA::decoding(QVector<BigInt> code)
{
    QString text;
    BigInt n, powe;
    long long t;
    for(auto i:code)
    {
        n = 1;
        powe = i;
        t = e.to_int();
        while(t--)
        {
            n = n * powe;
            n = n % N;
        }
        text.push_back(QChar(n.to_int()));
    }

    return text;
}
