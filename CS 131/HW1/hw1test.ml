(* subset tests *)

let my_subset_test_0 =
  subset [] [] = true;;

let my_subset_test_1 =
  subset [1;1;2;1;4;1;5;6;7;7;7;7;7;1;11;24] [1;1;2;3;4] = false;;

let my_subset_test_2 =
  subset ['a';'c';'e';'g';'i';'m';'o';'q';'s';'u';'w';'y';'b';'d';'f';'h';'j';'l';'n';
          'p';'r';'t';'v';'x';'z';'a';'e';'i';'m';'q';'u';'y';'c';'g';'o';'s';'w';'b';
          'f';'j';'n';'r';'v';'z';'d';'h';'l';'p']

          ['b';'d';'f';'h';'j';'l';'n';'p';'r';'t';'v';'x';'z';'c';'e';'g';'i';'k';'m';
           'o';'q';'s';'u';'w';'y';'b';'d';'h';'l';'p';'t';'v';'z';'f';'j';'n';'r';'x';
           'c';'g';'k';'o';'s';'w';'e';'i';'m';'q';'z'] = false;;

let my_subset_test_3 =
  subset ['a';'c';'e';'g';'i';'k';'m';'o']

  ['a';'c';'e';'g';'i';'k';'m';'o';'q';'s';'u';'w';'y';'b';'d';'f';'h';'j';'l';'n'] = true;;

let my_subset_test_4 =
    subset [1] [1] = true;;

let my_subset_test_5 =
  subset [1;3;5;7;9] [] = false;;

(* equal_sets tests *)

let my_equal_sets_test_0 =
  equal_sets [] [] = true;;

let my_equal_sets_test_1 =
  equal_sets [1;3;1] [1;3] = true;;

let my_equal_sets_test_2 =
  equal_sets [1;3;1] [1] = false;;

let my_equal_sets_test_3 =
  equal_sets ['a';'c';'e';'g';'i';'k';'m';'o';'q';'s';'u';'w';'y';'b';'d';'f';'h';'j';'l';'n';
              'p';'r';'t';'v';'x';'z';'a';'e';'i';'m';'q';'u';'y';'c';'g';'k';'o';'s';'w';'b';
              'f';'j';'n';'r';'v';'z';'d';'h';'l';'p']

  ['d';'h';'l';'p';'t';'v';'z';'f';'j';'n';'r';'x';'a';
   'c';'g';'k';'o';'s';'w';'e';'i';'m';'q'] = false;;

let my_equal_sets_test_4 =
  equal_sets ['a';'c';'e';'g';'i';'k';'m';'o';'q';'s';'u';'w';'y';'b';'d';'f';'h';'j';'l';'n';
              'p';'r';'t';'v';'x';'z';'a';'e';'i';'m';'q';'u';'y';'c';'g';'k';'o';'s';'w';'b';
              'f';'j';'n';'r';'v';'z';'d';'h';'l';'p']

  ['a';'c';'e';'g';'i';'k';'m';'o';'q';'s';'u';'w';'y';'b';'d';'f';'h';'j';'l';'n';
   'p';'r';'t';'v';'x';'z';'a';'e';'i';'m';'q';'u';'y';'c';'g';'k';'o';'s';'w';'b';
   'f';'j';'n';'r';'v';'z';'d';'h';'l';'p'] = true;;

(* set_union tests *)

let my_set_union_test_0 =
  set_union [] [] = [];;

let my_set_union_test_1 =
  set_union [1;3;1] [1;3;4;5;6] = [1;3;4;5;6];;

  let my_set_all_union_test_2 =
    set_union [1;2;3;4] [5;6;7;8] = (List.rev [1;2;3;4])@[5;6;7;8];;

(* set_all_union tests *)

let my_set_all_union_test_0 =
  set_all_union [[1];[2];[3];[4];[5];[6];[7];[8];[]] = ([1;2;3;4]@[5;6;7;8]);;

let my_set_all_union_test_1 =
  set_all_union [['a'];['c'];['e'];['g'];['i'];['k'];['m'];['o'];['q'];['s'];['u'];['w'];['y'];['b'];['d'];['f'];['h'];['j'];['l'];['n'];[]]

  = ['a';'c';'e';'g';'i';'k';'m';'o';'q';'s';'u';'w';'y';'b';'d';'f';'h';'j';'l';'n'];;

(* computed_fixed_point tests *)

let my_computed_fixed_point_test_0 =
  computed_fixed_point (=) (fun x -> (0.5 *. x) +. 1.) 0. = 2.;;

let my_computed_fixed_point_test_1 =
  computed_fixed_point (=) (fun x -> x) 7 = 7;;

let my_computed_fixed_point_test_2 =
  computed_fixed_point (=) (fun x -> (x *. x) /. 4.) 8. = infinity;;

let my_computed_fixed_point_test_3 =
  computed_fixed_point (=) (fun x -> (x /. 3.) +. 2.) 20. = 3.;;

(* computed_periodic_point tests *)

let my_computed_periodic_point_test_0 =
  computed_periodic_point (=) (fun x -> 2 * x) 1 0 = 0;;

let my_computed_periodic_point_test_0 =
  computed_periodic_point (=) (fun x -> (x * x) - 3) 2 1 = 1;;

(* whileseq tests *)

let my_whileseq_test_0 =
  whileseq (fun x -> x - 1) (fun x -> x >= 4) 11 = [11;10;9;8;7;6;5;4];;

(* filter_blind_alleys tests *)

type noise_nonterminals =
  | Sound | Machine | Radio | Beep | Boop | Bop;;

let noise_grammar =
  (Sound,
  [Machine, [T"..."; N Beep; N Boop];
   Beep, [T"beep"];
   Boop, [T"boop"];
   Bop, [T"bop"];
   Sound, [N Bop; N Bop; N Machine]]);;

let my_filter_blind_alleys_test_0 =
  filter_blind_alleys noise_grammar = noise_grammar;;

let noise_grammar_1 =
  (Sound,
  [Machine, [N Sound];
   Machine, [];
   Beep, [T"beep"];
   Boop, [T"boop"];
   Bop, [T"bop"];
   Sound, [N Bop; N Bop; N Machine];
   Sound, [N Machine; N Radio];
   Sound, [N Beep; N Bop; N Boop];
   Radio, [N Machine; N Sound; N Radio]]);;

let my_filter_blind_alleys_test_1 =
  filter_blind_alleys noise_grammar_1
  =
  (Sound,
  [Machine, [N Sound];
   Machine, [];
   Beep, [T"beep"];
   Boop, [T"boop"];
   Bop, [T"bop"];
   Sound, [N Bop; N Bop; N Machine];
   Sound, [N Beep; N Bop; N Boop]]);;