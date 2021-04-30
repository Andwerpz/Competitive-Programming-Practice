//package product1modulon;

import java.util.*;
import java.io.*;

public class product1modulon {
	
	public static boolean isCoprime(int a, int b) {
		for(int i = 2; i <= Math.min(a, b); i++) {
			if(a % i == 0 && b % i == 0) {
				return false;
			}
			while(a % i == 0) {
				a /= i;
			}
			while(b % i == 0) {
				b /= i;
			}
		}
		return true;
	}
	
	public static boolean isPrime(int a) {
		for(int i = 2; i < a; i++) {
			if(a % i == 0) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		TreeSet<Integer> nums = new TreeSet<Integer>();
		boolean isPrime = isPrime(n);
		long prod = 1;
		for(int i = 1; i < n; i++) {
			//System.out.println(i);
			if(isPrime || isCoprime(i, n)) {
				nums.add(i);
				prod *= (long) i;
				prod %= n;
			}
		}
		int noGood = (int) prod;
		StringBuilder fout = new StringBuilder();
		fout.append(nums.size() - (noGood != 1? 1 : 0)).append("\n");
		for(int i : nums) {
			if(i != noGood || noGood == 1) {
				fout.append(i).append(" ");
			}
		}
		System.out.println(fout);
	}
}
