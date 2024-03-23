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

