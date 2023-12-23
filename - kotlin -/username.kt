
//Codeforces - 1910A

//since all the ids are valid, just remove the first nonnegative integer you see going from the right. 

//"!!" after a function means that i assert that the result is never null. 
//"?" is safe? idk what this means exactly. 

fun main() {
    var t: Int = readLine()!!.toInt();
    while(t-- > 0) {
        var s: String = readLine()!!;
        var ans: String = "";
        for(i in s.indices.reversed()) {
            var c: Char = s[i];
            if('1' <= c && c <= '9') {
                ans = s.substring(0, i);
                break;
            }
        }
        println(ans);
    }
}