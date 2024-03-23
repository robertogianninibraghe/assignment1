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
//This class minimizer is the first naive implementation, is left only for reference,
//The functor below minimizer2 is more general because gives choices for
//both the learning rate and option between exact gradient and finite differences method
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

/*Implementaion of the search of the minimum with options to chose both the way to compute the learning
rate and the exact or finite differences methods for the gradient.
Choice of the lr is done via templates, in particular class templates, where the three classes Exponential,
inverse decay and Armijo are below. Each of them allows to to chose the corresponding way of computing 
the lr by defining their own operator ( ) that gives as output a double, the learning rate.
Minimizer2 instead implements the operator ( ) that gives as output the required minimum of the function,
while in input takes either both the function f and the gradient df and therefore uses exact gradient,
or if only the function f is passed centered finite differences is used. Also the operator ( ) of minimizer2 
calls the operator of the template lRate, so allowing to also chose the lr*/
template <class lRate>
class minimizer2
{
public: 
    vec operator()(F f, Fn df) //inputs are the function and the gradient
    {
        vec x0 = params.start_point;
        double f_val = f(x0);
        vec df_val = df(x0);
        vec x_new = x0;
        vec x_old = x0;
        double alpha = params.alpha_0;
        vec delta_x = x0;
        for (size_t i = 0; i < params.max_it; i++)
        {
            //std::cout << "Iterazione numero" << i << std::endl;
            //used for debugging
            for (size_t j = 0; j < params.dim; j++)
            {
                x_new[j] = x_old[j] - alpha * df_val[j];
                delta_x[j] = x_new[j] - x_old[j];
                x_old[j] = x_new[j];
            }
 
            if (std::abs(f(x_new) - f_val) < params.tolerance_r || norm(delta_x) < params.tolerance_s)
            {
                // std::cout<< "entro qui"<<std::endl;
                return x_new;
            }
            f_val = f(x_new);
            df_val = df(x_new);
            //here i call the method( ) of the instance search_alpha of the template class
            alpha = search_alpha(x_new, f_val, df_val, params.alpha_0, f, i, params.mu, params.sigma);   
        }
        std::cout << "Method reched the maximum number of iterations" << std::endl;
        return x_new;
    }
    //I overload the operator () in order to give the choice for finite differences or exact gradient.
    //If a gradient is passed exact gradient is used, otherwise if i only pass the function but not the 
    //gradient then automatically it's used the centered finite differences method
    //OSS: here in order to reuse code i decided to create a lambda that captures the function f and
    //given and input vector x computes the gradient by centered finite differences approximation. Then
    //both f and the lambda are passed to the operator ()(F f, Fn df) 
    vec operator()(F f){
        std::cout<<"Using finite differences method to compute the gradient"<<std::endl;
        auto fin_diff_grad= [&f]( const vec& x){
            double h=0.001;// chose a step for finite differences method
            unsigned n= x.size();
            vec grad=x;
            vec x_delta_plus=x;
            vec x_delta_minus=x;
            for (size_t i = 0; i < n; i++)
            {
                x_delta_minus[i]=x[i]-h;
                x_delta_plus[i]=x[i]+h;
                grad[i]=(f(x_delta_plus)-f(x_delta_minus))/(2*h);
                x_delta_minus[i]=x[i];
                x_delta_plus[i]=x[i];
            }
            return grad;
        };
        return this->operator()(f,fin_diff_grad );
    }

    parameters params;

private:
    lRate search_alpha;
};

//Below are the classes that implement the different ways of computing the learning rate, doing so by
//
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


