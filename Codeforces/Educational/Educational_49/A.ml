
let same a b =
  let a = Char.code a in
  let b = Char.code b in
  let diff = abs (a - b) in
  (diff == 0) || (diff == 2) ;;           

let solve () =
  let n = read_int() in
  let s = read_line() in

  let rec check str l r =
    if l > r then
      true
    else if same (String.get str l) (String.get str r) then
      true && (check str (l+1) (r-1))
    else false in
  
  let res = check s 0 (n - 1) in
  if res == true then
    print_string "YES"
  else
    print_string "NO" ;
  print_newline () ;;
     
let t = read_int () in
for i = 1 to t do 
  solve ()
done
