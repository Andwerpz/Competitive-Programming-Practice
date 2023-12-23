import java.util.*;
import java.io.*;
import kotlin.math.*;

@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out

@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readString() = read()
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }

@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }

//Codeforces - 1910F

//man, kotlin is a pain. 

//instead of thinking about building railroad stations on nodes, we can instead think about improving the edges. 
//for each edge, we can compute the number of paths going through it. Then, if we can build a rail through the edge,
//we can reduce the sum by exactly the number of paths through it. 

//We can show that it is always possible to remove the k - 1 edges with the most amount of paths through them. 

fun calcSubtSize(cur: Int, p: Int, c: ArrayList<ArrayList<Int>>, subt_size: ArrayList<Long>): Long {
    var ans: Long = 1;
    for(i in c.get(cur).indices) {
        var next = c.get(cur).get(i);
        if(next == p){
            continue;
        }
        ans += calcSubtSize(next, cur, c, subt_size);
    }
    subt_size.set(cur, ans);
    return ans;
}

fun calcEdgeCnt(cur: Int, p: Int, c: ArrayList<ArrayList<Int>>, subt_size: ArrayList<Long>, n: Int, edge_cnt: ArrayList<Long>) {
    for(i in c.get(cur).indices) {
        var next = c.get(cur).get(i);
        if(next == p){
            continue;
        }
        var subt = subt_size.get(next);
        var rest: Long = n - subt;
        edge_cnt.add(subt * rest);
        calcEdgeCnt(next, cur, c, subt_size, n, edge_cnt);
    }
}

fun main() {
    output {
        var t: Int = readInt();
        while(t-- > 0){
            var n: Int = readInt();
            var k: Int = readInt();
            var c = ArrayList<ArrayList<Int>>(0);
            for(i in 0 until n) {
                c.add(ArrayList<Int>());
            }
            for(i in 0..<(n-1)){
                var a = readInt();
                var b = readInt();
                a --;
                b --;
                c.get(a).add(b);
                c.get(b).add(a);
            }
            var edge_cnt = ArrayList<Long>(0);
            var subt_size = ArrayList<Long>(n);
            for(i in 0 until n){
                subt_size.add(0);
            }
            calcSubtSize(0, -1, c, subt_size);
            calcEdgeCnt(0, -1, c, subt_size, n, edge_cnt);
            edge_cnt.sortByDescending{it};
            var ans: Long = 0;
            for(i in edge_cnt.indices) {
                ans += edge_cnt.get(i);
                if(i >= k - 1) {
                    ans += edge_cnt.get(i);
                }
            }
            println(ans);
        }
    }   
}