# Study of Heat Conduction Equation

## Index

1. [Abstract](#abstract)
2. [Description](#description)
    1. [Problem definition](problem-definition)
    2. [Numerical analysis](numerical-analysis)
3. [Procedures](#procedures)

## Abstract 

Four numerical schemes were applied to compute a solution for a
parabolic partial differential equation, the heat conduction equation.
Two different types of schemes were used, explicit and implicit, and
their solutions were evaluated. It could be observed the different
behaviours of unstable and stable schemes. Step size variations of a
stable method were studied as well. The obtained solutions were compared
to the problem analytical solution in order to have a better
understanding on these different behaviours.

## Description

Numerical methods are used to obtain an approximated solution to
problems with no given analytical solution. These methods can be used in
order to save computational time, therefore they can obtain results
which are similar to the real solution more efficiently. Four different
schemes were applied to compute an approximated solution to a
**Parabolic Partial Differential Equation**, in this case the heat
conduction equation.

<p align="center"><img src ="./readme/0.png" /><p align="center">

This condition had to be satisfied on a grid in space and time, which
means the problem has a structured mesh type, and therefore can be
represented as a grid of two dimensions. The previous equation could be
written in its discretized form for each method.

#### Problem definition

A few initial or boundary conditions were set, including the heat
conduction equation. An existing wall with **1 *ft*** thick had an
initial temperature of **100ºF** and the surface temperatures at both
sides were suddenly increased and maintained to **300ºF**. It is also
known that the wall is composed of nickel steel (40% Ni) with a
Diffusivity of **0.01 $ft ^2/h$**.

Since the wall has a 1 *ft* thickness, the problem space domain could be
restricted between **0** and **1**, and the diffusivity value, which is
considered constant, could be set to **0.01**. The time domain was
restricted between **0** to **0.5**:

<p align="center"><img src ="./readme/1.png" /><p align="center">
    
The initial boundaries can be formalized in mathematical expressions:

<p align="center"><img src ="./readme/2.png" /><p align="center">

The analytical solution of this problem was given by the following
expression

<p align="center"><img src ="./readme/3.png" /><p align="center">
    
#### Numerical analysis

Numerical analysis is the study of the obtained solution. Criticism is
very important on this phase, since the solutions are evaluated. Digital
computers have problems with round-off errors, and since values were
truncated, problems with discretization errors may appear. There are
some definitions related with this study: stability, convergence and
approximation @convergence_stability_consistency [@numerical_analysis].

A method is declared stable if the error doesn’t grow as time advances.
Theoretically, conditions that make a scheme becomes stable or unstable
can be known.

Approximation can be verified by comparing the computed solution with
the analytical solution, and check if there is an approximation at all.

Convergence is defined by how well the computed solution approximates to
the analytical solution. This can vary with a change in the number of
**time steps** or **space steps**. A smaller number of steps can lead to
a bigger error, whereas a bigger number of steps can lead to a
considerably more time expensive solution. Every method could be
developed using **Taylor Series** @hoffman. This series were developed
for **n** terms. Thus, every method has a given approximation factor,
that could be represented in the **Big Oh** annotation. The error
related with this approximation is called **Truncation Error**
@numerical_analysis.

A quantitative analysis can be done by comparing solutions of each
method. By calculating the **norms** of the error matrix, one can
conclude which method is more accurate. The **error matrix** can be
calculated by subtracting each cell of the **analytical** solution
matrix to the cells of a method matrix. When the result is a matrix of
small values, the error is small. Whenever a norm is calculated, one is
able to translate an error matrix into a single value:

-   **One Norm** - Which is given by adding the absolute values of each
    cell of the matrix.

-   **Two Norm** - Which is obtained by adding the squares of every
    value in the matrix.

-   **Uniform Norm** - Which represents the biggest error, or the
    maximum value in the matrix.

The second norm “punishes” the biggest values, and “regards” the lowest
ones. Notice that a the square of a value between $0$ and $1$ is lower
than the given value. Whereas the square of a value bigger than 1 is
higher. Therefore, this norm is a good quality indicator.

A stencil could also be developed for each method, which relates the
several grid points, revealing the dependencies for a calculation in a
more graphical way.

## Procedures

Four different schemes/methods were used to compute a solution for the
given problem, two of them are explicit schemes, **Richardson**,
**DuFort-Frankel**, and two of them are implicit schemes, **Laasonen
Simple Implicit** and **Crank-Nicholson**. The space step was maintained
at **0.05** *ft*, and the time step took the value of **0.01** *h*,
studying every solutions in intervals of **0.1** hours from **0.0** to
**0.5**. The **Laasonen Simple Implicit** solution was also studied with
different time steps, always maintaining the same space step, **0.05**:

