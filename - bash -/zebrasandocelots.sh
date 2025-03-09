# touch 'for i in {1..3}; do echo "Loop $i"; done'  # Filename as a loop
# eval "$(ls)"
# touch "read n; ((a = 0)); for((i = 0; i < n; i++)); do read s; if [[ '$s' == 'O' ]]; then ((a = a + (1 << i))) fi; done; echo $a;"

# read n; ((a = 0)); for((i = 0; i < n; i++)); do read s; if [[ "$s" == "O" ]]; then ((a = a + (1 << n - 1 - i))) fi; done; echo $a;

# read n;((a=0));for((i=0;i<n;i++));do read s;if [[ "$s" == "O" ]]; then ((a=a+(1<<n-1-i))) fi;done;echo $a;
# read n;for((a=0;i++<n;)){ read s;[ $s = O ]&&((a+=(1<<n-i)));};echo $a;
#' ' -> z
#'(' -> x
#')' -> w
#'{' -> y
#'}' -> u
#';' -> q
#'$' -> 
#'+'
#'<'
#'['
#']'
#'&'
#'='

# touch '{ read s;[ $s = O ]&&((a=a+(1<<n-i)));};echo $a;';
touch 'read n;a=0;for((;i++<n;)){ read s;[ $s = O ]&&((a=a+(1<<n-i)));};echo $a;';
# touch 'i++<n;)){ read s;[ $s = O ]&&((a+=(1<<n-i)));};echo $a;';

# read n;a=0;for((;

# read n;
# ((a = 0));
# for((i = 0; i < n; i++)); do
#     read s;
#     if [[ "$s" == "O" ]]; then
#         ((a = a + (1 << n - 1 - i)))
#     fi;
# done;
# echo $a;