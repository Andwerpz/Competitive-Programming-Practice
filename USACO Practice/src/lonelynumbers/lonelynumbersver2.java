package lonelynumbers;

import java.util.*;
import java.io.*;

public class lonelynumbersver2 {
	public static void main(String[] args) throws IOException {
		
		//1423K
		
		//the observation is that first, all composite numbers are not lonely, and second, for a given value of n, all primes <= sqrt(n) are not lonely. 
		//1 is always lonely. So the solution is to first generate all primes up to 10^6, construct a pfx sum giving the number of primes below a number. 
		//then for any given value of n, the number of lonely numbers is the number of primes that are strictly greater than sqrt(n) + 1. +1 for 1, which we didn't consider as prime
		//but is always lonely. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		boolean[] sieve = new boolean[1000001];
		int[] pfx = new int[1000001];
		for(int i = 2; i < sieve.length; i++) {
			if(!sieve[i]) {
				pfx[i] ++;
				int index = i * 2;
				while(index < sieve.length) {
					sieve[index] = true;
					index += i;
				}
			}
			pfx[i] += pfx[i - 1];
		}
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < t; i++) {
			int next = Integer.parseInt(st.nextToken());
			int low = (int) Math.floor(Math.sqrt(next));
			//System.out.println(low + " " + next);
			fout.append((pfx[next] - pfx[low]) + 1).append(" ");
		}
		System.out.println(fout);
	}
}
