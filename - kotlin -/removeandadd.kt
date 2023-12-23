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

//Codeforces - 1910D

//find the maximum prefix and suffix that you can fix by only adding 1 to elements. 

//then, using the remove 1 element, figure out if you can combine any two prefix and suffixes. 

fun main() {
    output {
        var t: Int = readInt();
        while(t-- > 0){
            var n: Int = readInt();
            var a: IntArray = readIntArray(n);
            var pfx: IntArray = IntArray(n + 2) {1000000000};
            var sfx: IntArray = IntArray(n + 2) {-1000000000};
            pfx[0] = -1;
            sfx[n + 1] = 1000000000;
            for(i in a.indices) {
                if(a[i] >= pfx[i]) {
                    if(a[i] == pfx[i]) {
                        pfx[i + 1] = a[i] + 1;
                    }
                    else {
                        pfx[i + 1] = a[i];
                    }
                }
                else {
                    break;
                }
            }
            for(i in a.indices.reversed()) {
                if(a[i] < sfx[i + 2]) {
                    if(a[i] == sfx[i + 2] - 1) {
                        sfx[i + 1] = a[i];
                    }
                    else {
                        sfx[i + 1] = a[i] + 1;
                    }
                }
                else {
                    break;
                }
            }
            var is_valid: Boolean = false;
            for(i in 1..n) {
                if(pfx[i - 1] < sfx[i + 1]) {
                    is_valid = true;
                }
            }
            println(if(is_valid) "YES" else "NO")
        }
    }   
}