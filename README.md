# Minimal C++ least squares fit

**Minimal C++ least squares fit** is a library built in C++ to find the coefficient for the high-order term in the running of an algorithm time in an efficient way and without using 3rd party libraries. We will calculate the scalability curve as the equation describing the asymptotic properties of an algorithm adn we will determine the coeficient by a least squares fit for the higher order term by minimizing the sum of squares of relative error.

The implementation will consider two cases:
* General case in the form of T = C * f(n) (with f(n) equal to the tipical escalability curves e.g. N, logN, NlogN,...)
* Special case O(1)

### General case T = C * f(n)

 As an example, let´s consider the algorithm Merge Sort whose asymptotic runtime is well knwon to have O(N log N), and we will represent it in the form:
 
 T = C * N log N
 
 where T is the predicted run time on input of size n and C is the coeficcient.
 
Applying the method of least squares for finding the coefficient C, given the actual timing data as:

| Input Size    | Measured Runtime | 
| :-------------: |:-------------:|
| N1            | T1            |
| N2            | T2            |
| N3            | T3            |
| ...           | ...           |
| Nk            | Tk            |

and defining scalability form as

f(n) = C * g(n) 

and we get that the total square error of the approximation is given by:

E = Σ[ti - f(ni)]**2 

where the sum is taken from i = 1 to i = k, k being the number of data points. The key observation in the method of least squares is that total square error E is minimized when the gadient of E is zero, that is, where the partial derivative with respect to the variable (DcE) is zero. Calculating this partial derivative gives: 

DcE = 2 Σ[ti - f(ni)] * Dcf

This gives the partial derivative of E in terms of those of f, which may be calculated to be: 

Dcf = g(n) 

Substituting this into the previous formula and setting the results equal to zero yields the following equation: 

C * Σ (g(ni))**2 = Σ(ti * g(ni))

and rearranging we get: 

C = Σ(ti * g(ni)) / Σ (g(ni))**2

### Special case T = C

In the special case of an asymptotically constant time algorithm, represented in the form:

 T = C
 
 where T is the predicted run time on input of size n and C is the coeficcient.
 
Applying the method of least squares for finding the coefficient C, given the actual timing data as:

| Input Size    | Measured Runtime | 
| :-------------: |:-------------:|
| N1            | T1            |
| N2            | T2            |
| N3            | T3            |
| ...           | ...           |
| Nk            | Tk            |

and defining scalability form as

f(n) = C

and we get that the total square error of the approximation is given by:

E = Σ[ti - f(ni)]**2 

where the sum is taken from i = 1 to i = k, k being the number of data points. The key observation in the method of least squares is that total square error E is minimized when the gadient of E is zero, that is, where the partial derivative with respect to the variable (DcE) is zero. Calculating this partial derivative gives: 

DcE = 2 Σ[ti - f(ni)] * Dcf

This gives the partial derivative of E in terms of those of f, which may be calculated to be: 

Dcf = 1

Substituting this into the previous formula and setting the results equal to zero yields the following equation: 

C * Σ1 = Σti

and rearranging we get: 

C = Σ(ti) / k

