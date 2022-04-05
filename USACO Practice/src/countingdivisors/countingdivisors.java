//package countingdivisors;

import java.util.*;
import java.io.*;

public class countingdivisors {
	public static void main(String[] args) throws IOException {
		
		//CSES 1713
		
		//use linear sieve to generate the least prime factor for all numbers from 2 - 1e6. 
		
		//the number of divisors of a number is equal to multiplying all the (exponents + 1) of its prime factorization
		
		//since we have a list of least prime factors, we can easily generate the number of divisors of a number.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = (int) (1e6) + 1;
		int[] sieve = new int[n];
		ArrayList<Integer> primes = new ArrayList<Integer>();
		for(int i = 2; i < n; i++) {
			if(sieve[i] == 0) {
				sieve[i] = i;
				primes.add(i);
			}
			for(int j = 0; j < primes.size() && primes.get(j) <= sieve[i] && i * primes.get(j) < n; j++) {
				sieve[i * primes.get(j)] = primes.get(j);
			}
		}
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int x = Integer.parseInt(fin.readLine());
			int ans = 1;
			while(x > 1) {
				int lpf = sieve[x];
				int cnt = 0;
				while(x % lpf == 0) {
					x /= lpf;
					cnt ++;
				}
				ans *= (cnt + 1);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
