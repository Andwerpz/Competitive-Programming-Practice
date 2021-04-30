//package magicpowder;

import java.util.*;
import java.io.*;

public class magicpowder {
	
	static long[] recipe;
	static long[] leftover;
	static long k;
	
	public static boolean isValid(long val) {
		//just test how much magic powder we need to make val many cookies
		long sum = 0;
		for(int i = 0; i < recipe.length; i++) {
			sum += recipe[i] * val - Math.min(leftover[i], recipe[i] * val);
			if(sum > k) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		k = Long.parseLong(st.nextToken());
		recipe = new long[n];
		leftover = new long[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			recipe[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			leftover[i] = Integer.parseInt(st.nextToken());
		}
		long base = Integer.MAX_VALUE;
		for(int i = 0; i < n; i++) {
			base = Math.min(base, leftover[i] / recipe[i]);
		}
		for(int i = 0; i < n; i++) {
			leftover[i] -= recipe[i] * base;
		}
		long low = 0;
		long high = Integer.MAX_VALUE;
		long mid = low + (high - low) / 2;
		long ans = 0;
		while(low <= high) {
			if(isValid(mid)) {
				if(mid > ans) {
					ans = mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		//System.out.println(base);
		for(long i : leftover) {
			//System.out.print(i + " ");
		}
		//System.out.println();
		System.out.println(base + ans);
	}
}
