//package ropes;

import java.util.*;
import java.io.*;

public class ropes {
	
	public static boolean isValid(int[] ropes, double num, int k) {
		int sum = 0;
		for(int i = 0; i < ropes.length; i++) {
			sum += (int) Math.floor(ropes[i] / num);
		}
		if(sum >= k) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] ropes = new int[n];
		for(int i = 0; i < n; i++) {
			ropes[i] = Integer.parseInt(fin.readLine());
		}
		double high = Integer.MAX_VALUE;
		double low = 0;
		double mid = low + (high - low) / 2;
		double ans = low;
		while(high - low > Math.pow(10, -7)) {
			if(isValid(ropes, mid, k)) {
				if(ans < mid) {
					ans = mid;
				}
				low = mid;
			}
			else {
				high = mid;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
