
//Codeforces - 1910B

//locate the first minus and the last plus. If the minus is before the plus, then it's always 
//optimal to swap them. 

//use StringBuilder if you want mutable strings. 

fun main() {
    var t: Int = readLine()!!.toInt();
    while(t-- > 0){
        var s = StringBuilder(readLine()!!);
        var f_minus: Int = -1;
        var l_plus: Int = -1;
        for(i in s.indices) {
            if(s[i] == '-' && f_minus == -1) {
                f_minus = i;
            }
            if(s[i] == '+'){
                l_plus = i;
            }
        }
        var swapped: Boolean = false;
        if(f_minus != -1 && l_plus != -1 && f_minus < l_plus) {
            swapped = true;
            var tmp: Char = s[f_minus];
            s[f_minus] = s[l_plus];
            s[l_plus] = tmp;
        }
        var is_valid: Boolean = true;
        var cnt: Int = 0;
        for(i in s.indices) {
            cnt += if(s[i] == '+') 1 else -1;
            if(cnt < 0){
                is_valid = false;
                break;
            }
        }
        if(!is_valid) {
            println("-1");
        }
        else {
            if(swapped) {
                f_minus ++;
                l_plus ++;
                println("" + f_minus + " " + l_plus);
            }
            else {
                println("1 1");
            }
        }
    }
}