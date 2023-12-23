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

//Codeforces - 1910C

//got a nice io template, input is pretty convenient now, and it buffers all the output. 

//a frog can only be saved if there is a lily pad adjacent to it. 
//from there, we can easily observe that we can sacrifice one frog from each connected lily pad component
//to save the rest of them. 

fun main() {
    output {
        var t: Int = readInt();
        while(t-- > 0){
            var n: Int = readInt();
            var ans: Int = 0;
            for(i in 0..1){
                var s: String = readString();
                var cnt: Int = 0;
                for(j in s.indices) {
                    if(s[j] == '.') {
                        ans += max(0, cnt - 1);
                        cnt = 0;
                        continue;
                    }
                    else {
                        cnt ++;
                    }
                }
                ans += max(0, cnt - 1);
            }
            println("" + ans);
        }
    }   
}