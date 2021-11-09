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
		long mod = (long) (1e9 + 7);
		int counter = 0;
		for(int i = 2; i <= x; i++) {
			if(!isNotPrime[i]) {
				counter ++;
				ans *= 2;
				ans %= mod;
				for(int j = i * 2; j <= x; j += i) {
					isNotPrime[j] = true;
				}
			}
		}
		System.out.println(counter);
		System.out.println(ans);
	}
}
