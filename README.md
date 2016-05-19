# Minimal C++ least square fit

This is a library in C++ to find the coefficient for the high-order term in the running time without using 3rd party libraries. The calculation is done with a least-squares fit to minimize the sum of squares of relative error.

For example, the implementation of an algorithm named merge_sort(), is known to have asymptotic runtime Θ(n log n), and we will use the following for its form:

    T = C * N log N 

where T is the predicted run time on input of size n. To obtain the concrete scalability curve, we need to obtain actual timing data for the sort and use that data to find optimal values for the coefficient C. The method for finding this coefficient is the method of least squares. Assume that we have sample runtime data as follows:

    Input size:  	    n1	n2	...	nk
    Measured runtime:  	t1	t2	...	tk

and the scalability form is given by

    f(n) = C * g(n) 

Define the total square error of the approximation to be the sum of squares of errors at each data point:

    E = Σ [ti  -  f(ni)]2 

where the sum is taken from i = 1 to i = k, k being the number of data points. The key observation in the method of least squares is that total square error E is minimized when the gadient of E is zero, that is, where the partial derivatives with respect to the variables are zero. Calculating these partial derivatives gives:

    DXE	  =   2 Σ [ti  -  (C * g(ni))] Dcf(n)

Substituting this into the previous formula and setting the result equal to zero yields the following equation:

    C Σ (g(ni))2    =    Σ ti g(ni) 

Rearranging yields:

    C = Σ ti g(ni) / [Σ (g(ni))2]
