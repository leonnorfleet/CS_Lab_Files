type awksub_nonterminals =
  | Expr | Term | Lvalue | Incrop | Binop | Num;;

let my_grammar =
  Expr,
  [Expr, [T"("; N Expr; T")"];
    Expr, [N Num];
    Expr, [N Expr; N Binop; N Expr];
    Expr, [N Lvalue];
    Expr, [N Incrop; N Lvalue];
    Expr, [N Lvalue; N Incrop];
    Lvalue, [T"$"; N Expr];
    Incrop, [T"++"];
    Incrop, [T"--"];
    Binop, [T"+"];
    Binop, [T"-"];
    Num, [T"0"];
    Num, [T"1"];
    Num, [T"2"];
    Num, [T"3"];
    Num, [T"4"];
    Num, [T"5"];
    Num, [T"6"];
    Num, [T"7"];
    Num, [T"8"];
    Num, [T"9"]];;

let my_convert_grammar_test_0 =
  (((snd (convert_grammar my_grammar)) Expr) = [[T"("; N Expr; T")"]; [N Num]; [N Expr; N Binop; N Expr]; [N Lvalue]; [N Incrop; N Lvalue]; [N Lvalue; N Incrop];]);;

let my_convert_grammar_test_1 =
  (((snd (convert_grammar my_grammar)) Binop) = [[T"+"]; [T"-"]]);;

let my_parse_tree_leaves_test_0 =
  (parse_tree_leaves (Node ("1", [Leaf "Talk"; Node ("2", [Node ("3", [Leaf "like"; Leaf "Yoda"]); Node ("4", [Node ("5", [Node ("6", [Leaf "this"])])])]); Leaf "does"]))
  = ["Talk"; "like"; "Yoda"; "this"; "does"]);;

let my_parse_tree_leaves_test_1 = 
  ((parse_tree_leaves (Node ("+", [Leaf "uno"; Node ("*", [Leaf "dos"; Leaf "tres"; Node ("@", [Leaf "quatro"])]); Leaf "cinco"]))) = ["uno"; "dos"; "tres"; "quatro"; "cinco"]);;

let awkish_grammar =
  (Expr,
   function
     | Expr ->
         [[N Term; N Binop; N Expr];
          [N Term]]
     | Term ->
	 [[N Num];
	  [N Lvalue];
	  [N Incrop; N Lvalue];
	  [N Lvalue; N Incrop];
	  [T"("; N Expr; T")"]]
     | Lvalue ->
	 [[T"$"; N Expr]]
     | Incrop ->
	 [[T"++"];
	  [T"--"]]
     | Binop ->
	 [[T"+"];
	  [T"-"]]
     | Num ->
	 [[T"0"]; [T"1"]; [T"2"]; [T"3"]; [T"4"];
	  [T"5"]; [T"6"]; [T"7"]; [T"8"]; [T"9"]]);;

let my_make_matcher_test_0 =
  let accept_two = function
  | "2" :: t -> Some ("2" :: t)
  | _ -> None in

  ((make_matcher awkish_grammar accept_two ["--"; "$"; "("; "1"; ")"; "+"; "$"; "9"; "2"]) = Some ["2"]);;

type noise_nonterminals =
  | Sound | Machine | Radio | Beep | Boop | Bop;;

let noise_grammar =
  Sound,
  [Machine, [N Sound; N Machine; N Sound];
   Machine, [T"!!!"];
   Beep, [T"beep"];
   Beep, [T"Beep"];
   Boop, [T"boop"];
   Boop, [T"Boop"];
   Bop, [T"bop"];
   Bop, [T"Bop"];
   Sound, [N Bop; N Bop; N Machine];
   Sound, [N Beep; N Bop; N Boop]];;

let robo_frag = ["bop"; "Bop"; "Beep"; "Bop"; "Boop"; "!!!"; "Bop"; "bop"; "beep"; "bop"; "boop"; "!!!"; "Beep"; "Bop"; "Boop"];;

let my_make_parser_test =
  let extract x =
    match x with
    | Some x -> x
    | None -> (Node (Sound, [])) in

  (parse_tree_leaves (extract ((make_parser (convert_grammar noise_grammar) robo_frag))) = robo_frag);;

