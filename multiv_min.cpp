#include "multiv_min.hpp"
#include <cmath>
// #include"utils.hpp"

double norm(const vec &v)
{
    // forse c'è da mettere dim come parametro e non richiamare n tutte
    // le volte
    double norma = 0;
    for (size_t i = 0; i < v.size(); i++)
    {
        norma += v[i] * v[i];
    }
    return std::sqrt(norma);
}

// vec minimizer::solve(const vec &x0){
vec minimizer::solve(F f, Fn df)
{
    vec x0 = params.start_point;
    // double f_val=params.f(x0);
    double f_val = f(x0);

    vec df_val = df(x0);
    // vec df_val=params.df(x0);
    vec x_new = x0;
    vec x_old = x0;
    double alpha = params.alpha_0;
    vec delta_x = x0;

    for (size_t i = 0; i < params.max_it; i++)
    {

        for (size_t j = 0; j < params.dim; j++)
        {
            x_new[j] = x_old[j] - alpha * df_val[j];
            delta_x[j] = x_new[j] - x_old[j];
            x_old[j] = x_new[j];
        }
      
        if (std::abs(f(x_new) - f_val) < params.tolerance_r || norm(delta_x) < params.tolerance_s)
        {

            return x_new;
        }
        // f_val=params.f(x_new);
        // df_val=params.df(x_new);
        f_val = f(x_new);
        df_val = df(x_new);
        // alpha=search_alpha(x_new, f_val, df_val, alpha);
        alpha = search_alpha(x_new, f_val, df_val, alpha, f);
    }
    std::cout << "Method reched the maximum number of iterations" << std::endl;
    return x_new;
}

// double minimizer::search_alpha(const vec& x_k, const double f_val, const vec& df_val,const double alpha){
double minimizer::search_alpha(const vec &x_k, const double f_val, const vec &df_val, const double alpha, F f)
{

    double alpha_curr = alpha;
    // size_t dim=df_val.size();
    std::vector<double> f_diff = df_val;
    for (size_t i = 0; i < params.dim; i++)
    {
        f_diff[i] = x_k[i] - alpha_curr * df_val[i];
    }
    double norm2 = norm(df_val);
    // while ( !( f_val - params.f(f_diff)>= params.sigma*alpha_curr*norm2 ) )
    while (!(f_val - f(f_diff) >= params.sigma * alpha_curr * norm2))
    {
        alpha_curr *= 0.5;
        for (size_t i = 0; i < params.dim; i++)
        {
            f_diff[i] = x_k[i] - alpha_curr * df_val[i];
        }
    }

    return alpha_curr;
};
