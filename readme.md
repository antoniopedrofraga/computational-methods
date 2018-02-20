# Study of Heat Conduction Equation

## Index

1. [Abstract](#abstract)
2. [Description](#description)
    1. [Problem definition](problem-definition)
    2. [Numerical analysis](numerical-analysis)

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

<div style="text-align:center"><img src ="./readme/0.png" /></div>

This condition had to be satisfied on a grid in space and time, which
means the problem has a structured mesh type, and therefore can be
represented as a grid of two dimensions. The previous equation could be
written in its discretized form for each method.

#### 
