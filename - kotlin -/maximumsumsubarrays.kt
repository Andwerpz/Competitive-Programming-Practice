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

//Codeforces - 1910E

//we can split the problem into two cases and solve them seperately. 

//case 1: the optimal subarrays of a and b don't overlap
//in this case, we create a new array 'c', where c[i] = max(a[i], b[i]), and the solution is simply the maximum
//sum of two non-overlapping subarrays of c. 

//to find this, we can consider choosing a pivot 'i', and finding the maximum subarray in the prefix [0, i], and suffix
//[i + 1, n), and doing this for every i. We can precompute the maximum subarray in all prefixes and suffixes, and do 
//this in linear time. 

//case 2: the optimal subarrays of a and b overlap
//the solution will consist of 3 parts, a middle section where they overlap, and a left and right tail. 
//let's say that the middle section is the segment [l, r). 
//in the middle section, we just take the sum of both a and b in that segment. The left tail is going to be the maximum
//subarray that ends at index l - 1 of 'c', (c[i] = max(a[i], b[i])). Likewise for the right tail, but it starts at
//index r. 

//we can try all left starting points for the middle section 'l', and for each, find the optimal ending index; 'r'. 
//first, compute a pfx sum array, 'p', where p[i] = (a[0] + a[1] + ... + a[i - 1]) + (b[0] + b[1] + ... + b[i - 1]). 
//then, compute an array, 'r_tail', where r_tail[i] = maximum value of subarray starting at index i. 
//to compute r_tail, we can use kadane's algorithm
//then, for a given l, the optimal r is the index at which p[r] + r_tail[r] is maximal. 
//we can quickly find the optimal r by just iterating l backwards. 

//solution complexity : O(n).

fun main() {
    output {
        var t: Int = readInt();
        while(t-- > 0){
            var n: Int = readInt();
            var a: LongArray = readLongArray(n);
            var b: LongArray = readLongArray(n);
            var a_sum: LongArray = LongArray(n);
            var a_max: LongArray = LongArray(n);
            for(i in a.indices) {
                a_sum[i] = a[i] + b[i];
                a_max[i] = max(a[i], b[i]);
            }
            var ans: Long = 0;
            var l: LongArray = LongArray(n + 1) {0};
            var r: LongArray = LongArray(n + 1) {0};
            var pfx_sum: LongArray = LongArray(n + 1) {0};
            run {
                var r_sum: Long = 0;
                for(i in a_max.indices) {
                    r_sum = max(r_sum + a_max[i], a_max[i]);
                    l[i + 1] = max(0, r_sum);
                }
            }
            run {
                var r_sum: Long = 0;
                for(i in a_max.indices.reversed()) {
                    r_sum = max(r_sum + a_max[i], a_max[i]);
                    r[i] = max(0, r_sum);
                }
            }
            for(i in a_sum.indices) {
                pfx_sum[i + 1] = pfx_sum[i] + a_sum[i];
            }
            //assume combined
            run {   
                var max_sfx: Long = pfx_sum[n] + r[n];
                for(i in pfx_sum.indices.reversed()) {
                    ans = max(ans, l[i] + max_sfx - pfx_sum[i]);
                    max_sfx = max(max_sfx, pfx_sum[i] + r[i]);
                }
            }
            //assume seperate
            run {   
                for(i in a_max.indices) {
                    l[i + 1] = max(l[i], l[i + 1]);
                }
                for(i in a_max.indices.reversed()) {
                    r[i] = max(r[i], r[i + 1]);
                }
                for(i in l.indices) {
                    ans = max(ans, l[i] + r[i]);
                }
            }
            println(ans);
        }
    }   
}