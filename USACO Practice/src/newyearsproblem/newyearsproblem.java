//package newyearsproblem;

import java.util.*;
import java.io.*;

public class newyearsproblem {
	
	public static boolean isValid(int val, int[][] shops, int n, int m) {
		int[][] nums = new int[m][n];
		for(int i = 0; i < n; i++) {
			int count = 0;
			for(int j = 0; j < m; j++) {
				if(shops[j][i] >= val) {
					count ++;
					nums[j][i] = 1;
				}
			}
			if(count == 0) {	//a person can't be satisfied
				return false;
			}
		}
		for(int i = 0; i < m; i++) {
			int count = 0;
			for(int j = 0; j < n; j++) {
				if(nums[i][j] == 1) {
					count ++;
				}
			}
			if(count > 1) {	//there is a shop that can satisfy two or more people
				return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1619D
		
		//binary search through the possible maximum 'a' values. 
		
		//to check whether a given 'a' value is valid, you need to first check for each friend if you can get a gift for them, at or
		//above the given 'a' value. 
		
		//next, just check if you can get gifts for two friends at any given shop. If both are true, then the given 'a' value is valid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int m = Integer.parseInt(st.nextToken());
			int n = Integer.parseInt(st.nextToken());
			int[][] shops = new int[m][n];
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < n; j++) {
					shops[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			int ans = 0;
			int low = 0;
			int high = 1000000000;
			int mid = low + (high - low) / 2;
			while(low <= high) {
				if(isValid(mid, shops, n, m)) {
					ans = Math.max(ans, mid);
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
