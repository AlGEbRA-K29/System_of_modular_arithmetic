#ifndef ALL_FUNC_H
#define ALL_FUNC_H
#include <QString>
#include "all_func_call.h"

QString ff_addition(const QString x,const  QString& y,const  QString& z);

QString ff_subtraction(const QString& x, const QString& y,const  QString& z);

QString ff_multiply(const QString& x, const QString& y,const  QString& z);

QString ff_inverse(const QString& x, const QString& y,const  QString& z);

QString ff_division(const QString& x, const QString& y,const  QString& z);

QString ff_pow(const QString& x, const QString& y,const  QString& z);

QString ff_facrorization_naive(const QString& x);

QString ff_facrorization_polard(const QString& x);

QString ff_sqrt(const QString& x,const  QString& z);

QString ff_order(const QString& x, const  QString& z);

QString ff_generator(const QString& x, const  QString& z);

QString ff_euler(const QString& x);

QString ff_carmaicle(const QString& x);

QString ff_prime(const QString& x,const  QString& z);





QString pf_addition(const QString x,const  QString& y,const  QString& z, const  QString& ir);

QString pf_subtraction(const QString& x, const QString& y,const  QString& z, const  QString& ir);

QString pf_multiply(const QString& x, const QString& y,const  QString& z, const  QString& ir);

QString pf_normality(const QString& x,const  QString& z);

QString pf_fast_pow(const QString& x, const QString& y,const  QString& z, const  QString& ir);

QString pf_is_irred(const QString& x,const  QString& z);

QString pf_inverse(const QString& x,const  QString& z, const  QString& ir);




QString pr_addition(const QString x,const  QString& y,const  QString& z);

QString pr_subtraction(const QString& x, const QString& y,const  QString& z);

QString pr_multiply(const QString& x, const QString& y,const  QString& z);

QString pr_derivative(const QString& x,const  QString& z);

QString pr_value_in_point(const QString& x, const QString& y,const  QString& z);

QString pr_ring_divide(const QString& x, const QString& y,const  QString& z);

QString pr_ring_reminder(const QString& x, const QString& y,const  QString& z);

QString pr_ring_gcd(const QString& x, const QString& y,const  QString& z);

QString pr_get_cycled(const QString& x,const  QString& z);


#endif // ALL_FUNC_H
