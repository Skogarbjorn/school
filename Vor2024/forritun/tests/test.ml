let tl x =
    match x with
    | [] -> raise
        (Invalid_argument
            "attaemj jdlwajl ;"
        )
    | a::b -> b
;;

let result = tl [1;2;3]
in List.iter (Printf.printf "%d ") result;;
