#ifndef ALL_FUNC_H
#define ALL_FUNC_H
#include <QString>
#include "all_func_call.h"

QString ff_addition(const QString x,const  QString& y);

QString ff_subtraction(const QString& x, const QString& y);

QString ff_multiply(const QString& x, const QString& y);

QString ff_inverse(const QString& x, const QString& y);

QString ff_division(const QString& x, const QString& y);

QString ff_pow(const QString& x, const QString& y);

QString ff_facrorization_naive(const QString& x);

QString ff_facrorization_polard(const QString& x);

QString ff_sqrt(const QString& x);

QString ff_carmaicle(const QString& x);

QString ff_euler(const QString& x);

QString ff_prime(const QString& x);

QString ff_addition_mod(const QString x,const  QString& y,const  QString& z);

QString ff_subtraction_mod(const QString x,const  QString& y,const  QString& z);

QString ff_multiply_mod(const QString x,const  QString& y,const  QString& z);




QString pf_addition(const QString x,const  QString& y,const  QString& z);

QString pf_subtraction(const QString& x, const QString& y,const  QString& z);

QString pf_multiply(const QString& x, const QString& y,const  QString& z);


//QString pf_inverse(const QString& x, const QString& y,const  QString& z);

QString pf_normality(const QString& x,const  QString& z);

QString pf_fast_pow(const QString& x, const QString& y,const  QString& z);



QString pr_addition(const QString x,const  QString& y);

QString pr_subtraction(const QString& x, const QString& y);

QString pr_multiply(const QString& x, const QString& y);

QString pr_value_in_point(const QString& x, const QString& y);

QString pr_derivative(const QString& x);

QString pr_get_cycled(const QString& x);


#endif // ALL_FUNC_H
