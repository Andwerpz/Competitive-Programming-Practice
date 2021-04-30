package shorttask;

import java.util.*;
import java.io.*;

public class shorttaskver2 {
	
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
		int n = 10000;
		ArrayList<TreeSet<Integer>> dp = new ArrayList<TreeSet<Integer>>();
		dp.add(new TreeSet<Integer>());
		dp.add(new TreeSet<Integer>());
		dp.get(1).add(1);
		for(int i = 2; i <= n; i++) {
			System.out.println(i);
			dp.add(new TreeSet<Integer>());
			dp.get(i).add(i);
			dp.get(i).add(1);
			if(!isPrime(i)) {
				int a = 0;
				int b = 0;
				for(int j = 2; j < i; j++) {
					if(i % j == 0) {
						a = i;
						b = i / j;
						break;
					}
				}
				dp.get(i).addAll(dp.get(a));
				dp.get(i).addAll(dp.get(b));
			}
		}
		int[] ans = new int[n + 1];
		for(int i = 0; i <= n; i++) {
			int sum = 0;
			for(int j : dp.get(i)) {
				sum += j;
			}
			if(sum < ans.length && ans[sum] == 0) {
				ans[sum] = i;
			}
		}
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			System.out.println("loo");
			int next = Integer.parseInt(fin.readLine());
			fout.append(ans[next] == 0? "-1" : (ans[next])).append("\n");
		}
		System.out.print(fout);
	}
}
