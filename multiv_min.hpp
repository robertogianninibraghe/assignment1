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
    minimizer(parameters parametri): params(parametri);
    vec solve(const vec &x0){
        //need to check if dim written like this is visible
        for (size_t i = 0; i < dim; i++)
        {
            /* code */
        }
        
    }

    /*std::vector<double> solve(const std::vector<double> &x0){
        for(unsigned n_it=0; n_it< params.max_it(); ++n_it){
        }
    } */ //fine del solve

    //da vedere quali metodi vanno const e quali no
    double search_alpha(const vec& x_k, const double f_val, const vec& df_val,const double alpha){
        double alpha_curr=alpha;
        //size_t dim=df_val.size();
        std::vector<double> f_diff=df_val;
        for (size_t i = 0; i < dim; i++)
        {
            f_diff[i]=x_k[i] - alpha_curr*df_val[i];   
        }
    
        double norm2=norm(df_val);
        while ( !( f_val - f(f_diff)>= sigma*alpha_curr*norm2 ) )
        {
            alpha_curr*= 0.5;
            for (size_t i = 0; i < dim; i++)
            { 
               f_diff[i]=x_k[i] - alpha_curr*df_val[i];   
            } 
        }

        return alpha_curr;
        
    }


};

//voglio usare i templates qui anzichè quello che ho usato
//std::vector<double> multiv_min(std::function<double(double const &, double  const &)> const &f,
//                  std::function<double(double const &, double  const &)> const &Df, T const & strategy, parameters param ){};

// versione più generica
 
//std::vector<T> min_2(std::function<)
#endif