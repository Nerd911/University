:- use_module(library(clpfd)).
indomain(Var, L..U) :-
  L1 is L + 1,
  L1 =< U,
  indomain(Var, L1..U).
indomain(Var, Var.._) :- !.
indomain(Var, D1\/D2) :-
  indomain(Var, D1);
  indomain(Var, D2), !.
indomain(Var, Var) :- !.
indomain(Var) :-
  fd_dom(Var, Domain),
  indomain(Var, Domain).
labeling([]) :- !.
labeling(Vars) :-
  select_var(Vars, Var, RVars),
  indomain(Var),
  labeling(RVars).
select_var([Var|Vars], Var, Vars).
