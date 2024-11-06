(*
Notkun: mapreduce f op u x
Fyrir: f er fall, op er tvíundaraðgerð,
       u er gildi og x er listi, x=[x1;...;xn]
Gildi: u XOR f(x1) XOR ... XOR f(xn)
*)
let rec mapreduce f op u x =
    match x with
    | [] -> u
    | a::b -> mapreduce f op (op u (f a)) b
;;

(*
Notkun: mapftwice f
Fyrir: f er fall sem tekur eitt viðfang af tagi 'a
Gildi: Fall sem tekur inn lista l=[l1;...;ln] af tagi 'a sem viðfang 
       og skilar [f(f(l1));...;f(f(ln))]
*)
let mapftwice f =
    (*
    Notkun: gamer x
    Fyrir: x er listi, x=[x1;...;xn]
    Gildi: [f(f(x1));...;f(f(xn))]
    *)
    let rec gamer l =
        match l with
          [] ->
            []
        |
          a::b ->
            (f (f a)) :: (gamer b)
    in 
      gamer
;;

(* EINSTAKLINGSVERKEFNI *)

let rec list_it f x u =
    match x with
    | [] -> u
    | a::b -> f a (list_it f b u)
;;

(*
Notkun: lengd x
Fyrir: x er listi gilda af hvaða tagi sem er, x=[x1;...;xn]
Gildi: Lengd listans
*)
let lengd x =
    list_it (fun _ y -> 1+y) x 0
;;

(*
Notkun: powerList x
Fyrir: x er listi, x=[x1;x2;...;xn]
Gildi: Listi allra mögulegra lista sem eru undirlistar
       listans x. Fjöldi staka er þá 2^n
*) let rec powerList x =
    match x with
      [] -> [[]]
      | x::xs ->
          let rest = powerList xs
          in rest @ List.map (fun l -> x::l) rest
;;

let
  result = lengd []
in 
  Printf.printf "Lengd: %d\n" result;;

let () = Printf.printf "Mapftwice: [";;
let inc x =
  x+1
in 
  let f = 
    mapftwice inc
  in 
    let result = f [1;2;3]
  in 
    List.iter (Printf.printf "%d ") result;;
let () = Printf.printf "]\n";;


Printf.printf "PowerList: "
let () =
  let print_list l = 
    print_string "[";
    List.iter (fun x -> print_int x; print_string "; ") l;
    print_string "]"
  in 
    let print_power_list pl =
      print_string "[";
      List.iter (fun l -> print_list l; print_string "; ") pl;
      print_string "]\n"
    in
      print_power_list (powerList [])
;;

let 
  inc x = x+1
and 
  mul x y = x*y
in 
  let result = mapreduce inc mul 1 [0;1;2;3;4]
in 
  Printf.printf "Mapreduce: %d\n" result;;








