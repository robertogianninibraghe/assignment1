# Challenge 1. A gradient method for the minimization of a multivariate function

Repository for the first challenge of the course PACS. 
<br>
Given a function $f: R^n → R$ I implemented a gradient-based optimizer for solving the problem: $$x = argmin_{y \in R^n} \ f(y)$$
<br>
through a gradient method of the form: $$x_{k+1} = x_k - \alpha_k  \nabla f(x_k),  \ k=0,1,.., k_{max}$$
using the Armijo rule for computing the learning rate $\alpha_k$: 
$$f(x_k) - f(x_k - \alpha_0 \nabla f(x_k)) \geq \sigma \alpha_0 ||\nabla f(x_k)||^2$$
If hold then $\alpha_k = \alpha_0$, if not then take $\alpha_0 = \alpha_0 / 2$ and repeat until the condtion is satisfied.
Also gave the option to compute the learning rate $\alpha_k$ by exponential decay:
$$\alpha_k = \alpha_0 e^{- \mu k}$$
Or inverse decay:
$$\alpha_k = \frac{\alpha_0}{1 + \mu k}$$

# Implemenation, additional information
- All implementations are done insied the files multiv_min.hpp/cpp, while main.cpp allows to run some tests

- All the relevant parameters are kept inside the struct parameters

- The code implements firstly a naive class, minimizer, that simply allows to implement the said gradient descent method by Armijo's rule, given in input the function to be minimized and the gradient, while also containing all other relevant parameters inside a struct member, this first implementation is kept just for comparison.

- Then there is the implementation of minimizer2 which also allows to chose the method to compute the learning rate and also to choose between exact gradient and centered finite differences method for gradient approximation. The choice of the lr is done via templates, in particular class templates, where the three classes Exponential. Each of them allows to to chose the corresponding way of computing the lr by implementing their own operator ( ) that gives as output a double, the learning rate. Minimizer2 instead implements the operator ( ) that gives as output the required minimum of the function,while in input takes either both the function f and the gradient df and therefore uses exact gradient, or if only the function f is passed the centered finite differences method is used(so overloading of operator ( ) ). Also the operator ( ) of minimizer2 calls the operator ( ) of the template lRate, so allowing to also chose the lr

- To compile and run the code:
 ```bash
make 
./main
```

