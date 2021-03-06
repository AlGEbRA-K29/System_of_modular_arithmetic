#include "all_func.h"
#include <QTextStream>

QString ff_addition(const QString x,const  QString& y, const  QString& z){
    std::stringstream ss;
    ss << finFieldAddition(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_subtraction(const QString& x, const QString& y,const  QString& z){
    std::stringstream ss;
    ss << finFieldSubstraction(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_multiply(const QString& x, const QString& y,const  QString& z){
    std::stringstream ss;
    ss << finFieldMultiplication(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_inverse(const QString& x, const QString& y,const  QString& z){
    std::stringstream ss;
    ss << finFieldInverse(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_division(const QString& x, const QString& y,const  QString& z){
    std::stringstream ss;
    ss << finFieldDivision(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_pow(const QString& x, const QString& y,const  QString& z){
    std::stringstream ss;
    ss << finFieldPow(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_facrorization_naive(const QString& x){
    vector<bigint> vector_res = finFieldFacrorizationNaive(x.toStdString());
    QString res;
    for(const bigint& elem : vector_res){
        std::stringstream ss;
        ss << elem;
        res +=  QString::fromStdString(ss.str());
        res += " ";
    }
    return res;
}

QString ff_facrorization_polard(const QString& x){
    vector<bigint> vector_res = finFieldFacrorizationPolard(x.toStdString());
    QString res;
    for(const bigint& elem : vector_res){
        std::stringstream ss;
        ss << elem;
        res +=  QString::fromStdString(ss.str());        
        res += " ";
    }
    return res;
}

QString ff_sqrt(const QString& x,const  QString& z){
    std::stringstream ss;
    optional<pair<bigint, bigint>> answer = finFieldSqrt(x.toStdString(), z.toStdString());
    if (answer.has_value()) {
             ss << answer.value().first << " " << answer.value().second;
        }
    else {
        ss << "?????????????? ??????????";
    }
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_order(const QString& x, const QString& z){
    std::stringstream ss;
    ss << finFieldOrder(x.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_generator(const QString& x, const QString& z){
     std::stringstream ss;
    ss << finFieldIsGenerator(x.toStdString(), z.toStdString());
    bool b_res;
    istringstream(ss.str()) >> b_res;
    if(b_res){
        return "?? ??????????????????????";
    }
    else{
        return "???? ?? ??????????????????????";
    }
}

QString ff_euler(const QString& x){
    std::stringstream ss;
    ss << finFieldEuler(x.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString ff_carmaicle(const QString& x){
    std::stringstream ss;
    ss << finFieldCarmaicle(x.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}
QString ff_prime(const QString& x, const  QString& z){

    std::stringstream ss;
    ss << finFieldPrime(x.toStdString(),z.toStdString());
    bool b_res;
    istringstream(ss.str()) >> b_res;
    if(b_res){
        return "?? ??????????????";
    }
    else{
        return "???? ?? ??????????????";
    }
}
/*
*theme PolField
*/
QString pf_addition(const QString x,const  QString& y,const  QString& z, const  QString& ir){
    std::stringstream ss;
    ss << polFieldAddition(x.toStdString(),y.toStdString(),z.toStdString(),ir.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pf_subtraction(const QString& x, const QString& y,const  QString& z, const  QString& ir){
    std::stringstream ss;
    ss << polFieldSubtraction(x.toStdString(),y.toStdString(),z.toStdString(),ir.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pf_multiply(const QString& x, const QString& y,const  QString& z, const  QString& ir){
    std::stringstream ss;
    ss << polFieldMultiply(x.toStdString(),y.toStdString(),z.toStdString(),ir.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pf_normality(const QString& x, const  QString& z){
    std::stringstream ss;
    ss << polFieldNormality(x.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pf_fast_pow(const QString& x, const QString& y,const  QString& z, const  QString& ir){
    std::stringstream ss;
    ss << polFieldFastPow(x.toStdString(),y.toStdString(),z.toStdString(),ir.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pf_is_irred(const QString& x, const  QString& z){
    std::stringstream ss;
    ss << polFieldIsIrred(x.toStdString(),z.toStdString());
    bool b_res;
    istringstream(ss.str()) >> b_res;
    if(b_res){
        return "??????????????????";
    }
    else{
        return "??????????????";
    }
}

QString pf_inverse(const QString& x, const  QString& z, const  QString& ir){
    std::stringstream ss;
    ss << polFieldGetInverse(x.toStdString(),z.toStdString(),ir.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}
/*
*theme PolRing
*/
QString pr_addition(const QString x,const  QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingAddition(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_subtraction(const QString& x, const QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingSubtraction(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_multiply(const QString& x, const QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingMultiply(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_derivative(const QString& x, const  QString& z){
    std::stringstream ss;
    ss << polRingDerivative(x.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_value_in_point(const QString& x, const QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingValueInPoint(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_ring_divide(const QString& x, const QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingDivide(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_ring_reminder(const QString& x, const QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingRemainder(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_ring_gcd(const QString& x, const QString& y, const  QString& z){
    std::stringstream ss;
    ss << polRingGCD(x.toStdString(),y.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}

QString pr_get_cycled(const QString& x, const  QString& z){
    std::stringstream ss;
    ss << polRingGetCycled(x.toStdString(),z.toStdString());
    QString res =  QString::fromStdString(ss.str());
    return res;
}



