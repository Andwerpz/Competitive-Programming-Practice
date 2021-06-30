package ajarofworm;

import java.util.*;
import java.io.*;

public class ajarofworm {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int x = Integer.parseInt(fin.readLine());
		boolean[] isNotPrime = new boolean[x + 1];
		long ans = 1;
		long mod = 1000000007;
		for(int i = 2; i <= x; i++) {
			if(!isNotPrime[i]) {
				ans *= 2;
				ans %= mod;
				for(int j = i * 2; j <= x; j += i) {
					isNotPrime[j] = true;
				}
			}
		}
		System.out.println(ans);
	}
}
