type ('nonterminal, 'terminal) symbol =
  | N of 'nonterminal
  | T of 'terminal

type ('nonterminal, 'terminal) parse_tree =
  | Node of 'nonterminal * ('nonterminal, 'terminal) parse_tree list
  | Leaf of 'terminal

(* helper function to gather the list of nonterminal types from the 2nd element of the grammar tuple*)
(*on second thought this one wasnt really needed since the symbol is an input*)
let rec get_nts lst rls =
  match rls with
  | [] -> []
  | (a, b) :: t ->
    if List.exists (fun x -> x = a) lst then
      get_nts lst t
    else
      a :: get_nts (a :: lst) t;;

(*extract the right hand side of any tuple in the list*)
let rec get_rhs rls = 
  match rls with
  | [] -> []
  | (a, b) :: t -> b :: get_rhs t;;

let convert_grammar gram1 =
  (fst gram1),

  fun nt -> get_rhs (List.filter (fun x -> (fst x) = nt) (snd gram1));;
  (* List.filter(fun x -> (fst x) = smbl) rls;; *)
  (*this is the function that filters the tuples that match the corresponding symbol in the rules list*)

let rec parse_tree_leaves tree =
  match tree with
  | Leaf t -> [t]
  | Node (n, h :: t) -> (parse_tree_leaves h) @ (expand t)
  | _ -> []

and expand lst = 
  (*to iterate across a list left to right*)
  match lst with
  | [] -> []
  | h :: t -> parse_tree_leaves h @ expand t;;

let rec traverse_list grammar start lst accept frag =
  match lst with
  | [] -> None (*base case for if we have something like (Expr, [])*)
  | h :: t ->
    match (match_rule grammar h accept frag) with (*dfs on grammar tree result*)
    | Some x -> Some x (*found an accepted suffix*)
    | None -> traverse_list grammar start t accept frag (*try to match the next rule*)

and match_rule grammar rule accept frag =
  match rule with
  | [] -> accept frag (*no symbols left to try on this match attempt*)
  | h :: t ->
    match h with
    | T term -> (*we found a terminal symbol*)
      (match frag with
      | [] -> None
      | x :: v ->
        if (term = x) then
          match_rule grammar t accept v (*try to match the rest of the frag*)
        else
          None (*backtrack*))
    | N nonterm -> (*nonterminal symbol found*)
        let match_result = match_rule grammar t accept in (*keep going to see if we get an accept or None*)
        traverse_list grammar nonterm (grammar nonterm) match_result frag;;

let make_matcher gram =
  (*
  enter the function with the start symbol -> get the list of right hand sides
  -> perform left to right dfs on this (like parse_tree_leaves) -> for each symbol either match it with a frag element(T t)
  or keep going deeper for a match (N n)
  *)
  fun accept frag -> traverse_list (snd gram) (fst gram) ((snd gram) (fst gram)) accept frag;;


(*repurposing the functions for make_matcher*)
(*could probably use the result of make_matcher calls in place of reusing the dfs code*)
let rec traverse_list_parser grammar start lst accept frag tree =
  match lst with
  | [] -> None
  | h :: t ->
    match (parse_rule grammar start h accept frag tree) with
    | Some x -> Some x
    | None -> traverse_list_parser grammar start t accept frag tree

and parse_rule grammar start rule accept frag tree =
  match rule with
  | [] -> accept frag (Node (start, tree))
  | h :: t ->
    match h with
    | T term ->
      (match frag with
      | [] -> None
      | x :: v ->
        if (term = x) then
          parse_rule grammar start t accept v (tree @ [Leaf term])
        else
          None)
    | N nonterm ->
      let parse_result f2 t2 = parse_rule grammar start t accept f2 (tree @ [t2]) in
      traverse_list_parser grammar nonterm (grammar nonterm) parse_result frag [];;

let make_parser gram =
  let accept frag tree =
    match frag with
    | [] -> Some tree
    | _ -> None in

  fun frag -> traverse_list_parser (snd gram) (fst gram) ((snd gram) (fst gram)) accept frag [];;