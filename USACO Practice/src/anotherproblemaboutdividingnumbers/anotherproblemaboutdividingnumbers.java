//package anotherproblemaboutdividingnumbers;

import java.util.*;
import java.io.*;

public class anotherproblemaboutdividingnumbers {
	public static void main(String[] args) throws IOException {
		
		//1538D
		
		//the number of times you can divide the numbers is equal to the sum of prime factors of both numbers. 
		//special case is k = 1. This only works if one number is divisible by another number.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		boolean[] isPrime = new boolean[31624];
		ArrayList<Integer> primes = new ArrayList<Integer>();
		Arrays.fill(isPrime, true);
		for(int i = 2; i < isPrime.length; i++) {
			if(isPrime[i]) {
				primes.add(i);
				for(int j = i * 2; j < isPrime.length; j += 2) {
					isPrime[j] = false;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			boolean isValid = false;
			if(a == 1 && b == 1) {
				
			}
			else if(k == 1) {
				if((a % b == 0 || b % a == 0) && a != b) {
					isValid = true;
				}
			}
			else {
				int numFactors = 0;
				for(int j = 0; j < primes.size() && primes.get(j) <= a; j++) {
					int prime = primes.get(j);
					while(a % prime == 0) {
						a /= prime;
						numFactors ++;
					}
				}
				if(a != 1) {
					numFactors ++;
				}
				for(int j = 0; j < primes.size() && primes.get(j) <= b; j++) {
					int prime = primes.get(j);
					while(b % prime == 0) {
						b /= prime;
						numFactors ++;
					}
				}
				if(b != 1) {
					numFactors ++;
				}
				if(k <= numFactors) {
					isValid = true;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
