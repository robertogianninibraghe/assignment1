#ifndef UTILS_HPP
#define UTILS_HPP
#include<cmath>
#include<functional>
#include<vector>  

using vec= std::vector<double>;
using F=std::function<double(const vec &)>;
using Fn=std::function<vec(const vec &)>;

template<typename T>


struct parameters
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
    unsigned dim=2;

};




double norm(const vec& v){
    //forse c'è da mettere dim come parametro e non richiamare n tutte
    //le volte
    double norma=0;
    for (size_t i = 0; i < v.size(); i++)
    {
        norma += v[i]*v[i];
    }
    return norma;
        
}




#endif