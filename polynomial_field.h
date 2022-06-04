#pragma once
#include <map>
#include "big_integers/bigint.h"
#include "polynomial_ring.h"

class PolynomialField {

    public:
        PolynomialField() = delete;

        PolynomialField(const polynomial_ring& pol) {
            if (pol.getDegree() == 0) {
                throw std::invalid_argument("Очікується неконстантний поліном");
            }

            setIrreducible(pol);
        };

        void setIrreducible(polynomial_ring pol) {
            pol.normalize();
            if (!pol.isIrreducible())
                throw std::invalid_argument("Поліном не є незвідним");
            else
                irreducible = pol;
        }


        polynomial_ring addition(const polynomial_ring& a, const polynomial_ring& b) const {
            //checkDegree(a);
            //checkDegree(b);

            polynomial_ring res = a + b;
            //std::cout << res << std::endl;
            res = res.remainder(res, irreducible);
            return res;
        }

        polynomial_ring subtract(const polynomial_ring& a, const polynomial_ring& b) const {
            //checkDegree(a);
            //checkDegree(b);

            polynomial_ring res = a - b;

            res = res.remainder(res, irreducible);
            return res;
        }

        polynomial_ring multiply(const polynomial_ring& a, const polynomial_ring& b) const {
            //checkDegree(a);
            //	checkDegree(b);

            polynomial_ring res = a * b;

            res = res.remainder(res, irreducible);
            return res;
        }


        polynomial_ring quickPow(const polynomial_ring& poly,bigint power) const {
            if (power < 1_BI) {
                throw std::invalid_argument("Значення потужності має бути більше 0");
            }

            //checkDegree(poly);

            polynomial_ring result({ 1_BI }, poly.getModulus());
            polynomial_ring multiplier = poly;

            while (!power.isZero()) {
                if (power % 2_BI == 0_BI) {
                    multiplier *= multiplier;
                    power /= 2;
                } else {
                    result *= multiplier;
                    --power;
                }
            }

            return result.remainder(result,irreducible);
        }


        //Bloshenko's code 10/10
        // функция возвращает обратный полином к полиному a 
        // полином n - полином поля
        // пример вызова функции :
        //
        //   polynomial_ring n("x^4+4x^3+x^2+1", 3_BI);
        //   PolynomialField f1(n);
        //   polynomial_ring a("x^2+x^1", 3_BI)
        //   auto inverse = f1.extended_Euclidean_algorithm(a, n);
        //   
        // inverse - ответ 
    
       polynomial_ring extended_Euclidean_algorithm(polynomial_ring a, polynomial_ring n){
           
        polynomial_ring t("0",a.getModulus());
        polynomial_ring r(n);
        polynomial_ring newt("1",a.getModulus());
        polynomial_ring newr(a);

        polynomial_ring zero("0",a.getModulus());
        while(newr.getData().size()!=0){
            polynomial_ring q = r.divide(r,newr);
            
            polynomial_ring r1 = r;
            r = newr;
            
            newr = r1-(q*newr);
            
            polynomial_ring t1 = t;
            t = newt;
            
            newt = t1-(q*newt);
        }

        if(r.getDegree() > 0) return polynomial_ring("0",a.getModulus());
        
        polynomial_ring res("1",r.getModulus());
        res = res.divide(res, r);
        res = res*t;
        res =res.remainder(res,irreducible);

        return res;
    }

    private:
        polynomial_ring irreducible;

        /*void checkDegree(const polynomial_ring& to_check) const {
            if (to_check.getDegree() > irreducible.getDegree()) {
                throw std::invalid_argument("Polynomial isn't in the field");
            }
        }*/
};
