#ifndef MULTIV_MIN_HPP
#define MULTIV_MIN_HPP

#include<iostream>
#include<utils.hpp>
#include<functional>
/* #include<Eigen>*/



template<typename T>

//using std::function<double(const std::vector<double> &)> as funz;

/*struct parameters
{
    double tolerance_r =10^(-6);
    double tolerance_s =10^(-6);
    T initial_cond;
    double alpha_0 = 1;
    double sigma=0.5;
    unsigned max_it=10000;
    std::function<double(const std::vector<double> &)> f;
    std::function<std::vector<double>(const std::vector<double> &)> df;
    T strategy;

};
template<typename T>
*/

class minimizer{
    private:
    parameters params;
    //double f_val=0;
    //std::vector<double> df_val;

    public:
    minimizer(parameters parametri): params(parametri){};
    vec solve(const vec &x0);
    //da vedere quali metodi vanno const e quali no
    double search_alpha(const vec& x_k, const double f_val, const vec& df_val,const double alpha);

};

//voglio usare i templates qui anzichè quello che ho usato
//std::vector<double> multiv_min(std::function<double(double const &, double  const &)> const &f,
//                  std::function<double(double const &, double  const &)> const &Df, T const & strategy, parameters param ){};
// versione più generica
//std::vector<T> min_2(std::function<)
#endif