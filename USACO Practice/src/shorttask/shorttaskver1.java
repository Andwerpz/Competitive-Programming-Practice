package shorttask;

import java.util.*;
import java.io.*;

public class shorttaskver1 {
	
	public static boolean isPrime(int a) {
		int high = (int) Math.ceil(Math.sqrt(a));
		for(int i = 2; i <= high; i++) {
			if(a % i == 0) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//if a number is prime, it's just divisible by itself and 1
		//if not prime, find two divisors of this number that isn't 1 or this number, and the set of both of those divisors are this numbers divisors.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = 100;
		int[] dp = new int[n + 1];
		dp[1] = 1;
		for(int i = 2; i <= n; i++) {	//10^7
			if(isPrime(i)) {
				dp[i] = 1 + i;
			}
			else {
				for(int j = 2; j < i; j++) {
					if(i % j == 0) {
						int div1 = j;
						int div2 = i / j;
						dp[i] = dp[div1] + dp[div2];
						break;
					}
				}
			}
			System.out.print(dp[i] + " ");
		}
		int[] ans = new int[n];
		for(int i = 0; i < ans.length; i++) {
			if(ans[dp[i]] == 0) {
				ans[dp[i]] = i;
			}
		}
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int c = Integer.parseInt(fin.readLine());
			fout.append(ans[c] == 0? -1 : ans[c]).append("\n");
		}
		System.out.print(fout);
	}
}
