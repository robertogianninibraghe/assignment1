#ifndef MULTIV_MIN_HPP
#define MULTIV_MIN_HPP

#include <iostream>
#include <functional>
#include <cmath>

using vec = std::vector<double>;
using F = std::function<double(const vec &)>;
using Fn = std::function<vec(const vec &)>;

double norm(const vec &v);

struct parameters
{
    double tolerance_r = std::pow(10, -6);
    double tolerance_s = std::pow(10, -6);
    vec start_point = {0, 0};
    double alpha_0 = 0.1;
    double mu = 0.2;
    double sigma = 0.1;
    unsigned max_it = 1000;
    unsigned dim = 2;
};

class minimizer
{
private:
    parameters params;

public:
    minimizer(parameters parametri) : params(parametri){};
    // vec solve(const vec& x0);
    vec solve(F f, Fn df);
    double search_alpha(const vec &x_k, const double f_val, const vec &df_val, const double alpha, F f);
};

template <class lRate>
class minimizer2
{
public:
    vec operator()(F f, Fn df)
    {
        vec x0 = params.start_point;
        // double f_val=params.f(x0);
        double f_val = f(x0);
        // std::cout<<"First f_val "<<f_val<<std::endl;
        vec df_val = df(x0);
        // vec df_val=params.df(x0);
        vec x_new = x0;
        vec x_old = x0;
        double alpha = params.alpha_0;
        vec delta_x = x0;
        // need to check if dim written like this is visible
        for (size_t i = 0; i < params.max_it; i++)
        {
            //std::cout << "Iterazione numero" << i << std::endl;
            //used for debugging
            for (size_t j = 0; j < params.dim; j++)
            {
                x_new[j] = x_old[j] - alpha * df_val[j];
                delta_x[j] = x_new[j] - x_old[j];
                x_old[j] = x_new[j];
                // std::cout<< x_old[0]<<"  "<<x_old[1]<<std::endl;
            }
            // std::cout<<"f_val non dovrebbe cambiare"<<f_val<<std::endl;
            // std::cout<<f(x_new)<<std::endl;

            // std::cout<<"Modulo differenza: "<<std::abs(f(x_new)-f_val)<<std::endl;
            // std::cout<<"Dstanza : "<< norm(delta_x)<<std::endl;
            // if(abs(params.f(x_new)-f_val) < params.tolerance_r /*|| norm(delta_x)< params.tolerance_s*params.tolerance_s*/ ){
            // std::cout<<params.tolerance_r<<": : "<<params.tolerance_s*params.tolerance_s<<std::endl;

            if (std::abs(f(x_new) - f_val) < params.tolerance_r || norm(delta_x) < params.tolerance_s)
            {
                // std::cout<< "entro qui"<<std::endl;
                return x_new;
            }
            f_val = f(x_new);
            df_val = df(x_new);
            // alpha=search_alpha(x_new, f_val, df_val, alpha);
            alpha = search_alpha(x_new, f_val, df_val, params.alpha_0, f, i, params.mu, params.sigma);
            
        }
        std::cout << "Method reched the maximum number of iterations" << std::endl;
        return x_new;
    }
    parameters params;

private:
    lRate search_alpha;
};

class Exponential
{
public:
    double operator()(const vec &x_k, const double f_val, const vec &df_val, const double alpha, F f, unsigned k, double mu, double sigma) const
    {
        //std::cout << "Chosing the learning rate by exponential decay " << std::endl;
        //std::cout << "alpha with exp: " << alpha * std::exp(-1 * mu * k) << std::endl;
        //commands i used to check if the methods were working properly

        return alpha * std::exp(-1 * mu * k);
    }
};

class Inverse_decay
{
public:
    double operator()(const vec &x_k, const double f_val, const vec &df_val, const double alpha, F f, unsigned k, double mu, double sigma) const
    {
        //std::cout << "Chosing the learning rate by inverse decay " << std::endl;
        //std::cout << "alpha with inverse " << alpha / (1 + mu * k) << std::endl;
        //commands i used to check if the methods were working properly
        return alpha / (1 + mu * k);
    }
};

class Armijo
{
public:
    double operator()(const vec &x_k, const double f_val, const vec &df_val, const double alpha, F f, unsigned k, double mu, double sigma) const
    {

        //std::cout << "Chosing the learning rate by Armijio " << std::endl;
        //commands i used to check if the methods were working properly

        double alpha_curr = alpha;
        // size_t dim=df_val.size();
        std::vector<double> f_diff = df_val;
        unsigned dimen = df_val.size();
        for (size_t i = 0; i < dimen; i++)
        {
            f_diff[i] = x_k[i] - alpha_curr * df_val[i];
        }
        double norm2 = norm(df_val);
        while (!(f_val - f(f_diff) >= sigma * alpha_curr * norm2))
        {
            alpha_curr *= 0.5;
            for (size_t i = 0; i < dimen; i++)
            {
                f_diff[i] = x_k[i] - alpha_curr * df_val[i];
            }
        }

        return alpha_curr;
    }
};

#endif


