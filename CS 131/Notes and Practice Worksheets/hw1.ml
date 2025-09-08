let rec subset a b =
    match a with
        | [] -> true
        | x :: y ->
            if List.exists (fun z -> z = x) b then
                subset y b
            else
                false;;

let equal_sets a b =
    (subset a b) && (subset b a);;

let rec set_union a b =
    match a with
    | [] -> b
    | x :: y ->
        if List.exists (fun z -> z = x) b then
            set_union y b
        else
            set_union y (x :: b);;

let rec set_all_union a =
    match a with
    | [] -> []
    | x :: y -> set_union x (set_all_union y);;

(*
let self_member s = ();;

This is not possible to write in OCaml because this would mean the set
simultaneously references and does not reference itself in its 
declaration/initialization. It would also have a non-finite length.
*)

let rec computed_fixed_point eq f x = 
    if eq (f x) x then
        x
    else
        computed_fixed_point eq f (f x);;

let rec computed_periodic_point eq f p x =
    let rec n_iters n x =
        if n = 0 then
            x
        else
            n_iters (n-1) (f x)
    in

    if eq (n_iters p x) x then
        x
    else
        computed_periodic_point eq f p (f x);;

let rec whileseq s p x =
    match (p x) with
    | false -> []
    | true -> x :: whileseq s p (s x);;

type ('nonterminal, 'terminal) symbol =
  | N of 'nonterminal
  | T of 'terminal;;

let filter_blind_alleys g =

    (* helper function to see if a symbol is terminal or is known to terminate/not loop back into itself*)
    let check_symbol symbol terminals =
        match symbol with
        | T x -> true
        | N y -> subset [y] terminals
    in

    (* check if the rules eventually terminate by comparing it with what we know terminates *)
    let rec check_if_terminates rhs terminals =
        match rhs with
        | [] -> true
        | x :: v ->
            if check_symbol x terminals then
                check_if_terminates v terminals
            else
                false
    in

    (* create a list of known symbols that terminate *)
    let rec build_term_list g terminals =
        match g with
        | [] -> terminals
        | (s, rhs) :: v ->
            if (check_if_terminates rhs terminals) && (not (subset [s] terminals)) then
                build_term_list v (s::terminals)
            else
                build_term_list v terminals
    in

    (* toss out rules that dont terminate and put the ones that do into buffer which starts as an empty list *)
    let rec toss_bad_rules rules terminals buffer =
        match rules with
        | [] -> buffer
        | (s, rhs) :: v ->
            if check_if_terminates rhs terminals then
                toss_bad_rules v terminals buffer@[(s, rhs)]
            else
                toss_bad_rules v terminals buffer
    in

    (* call build_term_list until you end up not removing anything anymore for the list of terminals *)
    (* im using computed_fixed_point and equal_sets for this *)
    (* we start with the list of rules and not knowing what is terminal so that is the starting condition*)
    (* toss_bad_rules returns the rules in reverse order, so I need to reverse it again *)

    fst g, List.rev (toss_bad_rules (snd g) (snd (computed_fixed_point 
                                        (fun a b -> equal_sets (snd a) (snd b))
                                        (fun c -> (fst c), (build_term_list (fst c) (snd c)))
                                        (snd g, [])
                                        )) []);;