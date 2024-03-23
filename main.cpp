//
// Test file r
//

#include <iostream>

#include "multiv_min.hpp"
#include <cmath>


using std::cout;

double f_test(const vec &x)
{
    return x[0] * x[1] + 4 * std::pow(x[0], 4) + x[1] * x[1] + 3 * x[0];
}

vec df_test(const vec &x)
{
    vec grad = {x[1] + 16 * std::pow(x[0], 3) + 3, x[0] + 2 * x[1]};
    return grad;
}

void print_vec(const vec &x){
    for(const auto & i : x){
        cout<< i << " "<<std::endl;
    }
}

int main(int argc, char **argv)
{
    parameters par;

    minimizer min(par);
    
    vec result = min.solve(f_test, df_test);
    cout<<"Old implementation of Armijo without choice of learning rate: "<<std::endl;
    print_vec(result);

    minimizer2<Exponential> solve_exp;
    minimizer2<Inverse_decay> solve_inv;
    minimizer2<Armijo> solve_arm;

    vec res_exp = solve_exp(f_test, df_test);
    vec res_inv = solve_inv(f_test, df_test);
    vec res_arm = solve_arm(f_test, df_test);

    cout << "Solution with exponential:"  << std::endl;
    print_vec(res_exp);
    cout << "Solution with inverse:" << std::endl;
    print_vec(res_inv);
    cout << "Solution with Armijo:"  << std::endl;
    print_vec(res_arm);

    vec res_arm_fin_diff=solve_arm(f_test);
    cout << "Solution with Armijo with finite differences:"  << std::endl;
    print_vec(res_arm_fin_diff);

    return 0;
}
