/**

Left Factoring Algorithim 
==============================

A -> alp B1 | alp B2 | alp B3...... | Y

then by left factoring you get 

A -> alp A'
A' -> B1 | B2 | B3 | B4 ........


Left recursion elimanation
================================

A -> A alp | B This is in left recursion

A -> B A'
A' -> alp A' | Ephi

Example
=============================

E -> E + T | T
T -> T * F | F
F -> (E) | id

Applying removal 
E -> TE'
E' -> + T E' | Ephi

T -> F T'
T' -> * F T' | Ephi

Last remains the same since no left recursion

**/

