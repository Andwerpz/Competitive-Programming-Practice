package countthearrays;

import java.util.*;
import java.io.*;

public class countthearraysver2 {
	
	static int n = 200043;
	static int mod = 998244353;
	static int[] fact = new int[n];
	
	public static int add(int x, int y){
	    x += y;
	    while(x >= mod) x -= mod;
	    while(x < 0) x += mod;
	    return x;
	}

	public static int mul(int x, int y)
	{
	    return (int) ((x * 1l * y) % mod);
	}

	public static int binpow(int x, int y) {
	    int z = 1;
	    while(y != 0) {
	        if((y & 1) != 0) {
	        	z = mul(z, x);
	        }
	        x = mul(x, x);
	        y >>= 1;
	    }
	    return z;
	}

	public static int inv(int x) {
	    return binpow(x, mod - 2);
	}

	public static int divide(int x, int y) {
	    return mul(x, inv(y));
	}

	public static void precalc(){
	    fact[0] = 1;
	    for(int i = 1; i < n; i++)
	        fact[i] = mul(fact[i - 1], i);
	}

	public static int C(int n, int k)
	{
	    return divide(fact[n], mul(fact[k], fact[n - k]));
	}

	public static void main(String[] args) throws IOException {
		
		//1312D
		
				//copy of the tutorial implementation.
				//my implementation was slightly off, but i had the right idea. I just need to know how to divide numbers that i have applied mod to.
		
		precalc();
	    int n, m;
	    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
	    StringTokenizer st = new StringTokenizer(fin.readLine());
	    n = Integer.parseInt(st.nextToken());
	    m = Integer.parseInt(st.nextToken());
	    int ans = 0;
	    if(n > 2)
	        ans = mul(C(m, n - 1), mul(n - 2, binpow(2, n - 3)));
	    System.out.println(ans);
	}
}
