//package increasingbymodulo;

import java.util.*;
import java.io.*;

public class increasingbymodulo {
	
	static int[] nums;
	static int m;
	
	public static boolean isValid(int val) {
		int max = 0;
		for(int i = 0; i < nums.length; i++) {
			int next = nums[i];
			if(next + val >= m + max) {
				next = max;
			}
			else {
				if(next < max) {
					if(next + val < max) {
						return false;
					}
					else {
						next = max;
					}
				}
			}
			//System.out.print(next + " ");
			max = Math.max(next, max);
		}
		//System.out.println();
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1168A
		
		//binary search through the number of operations.
		//since you can choose as many numbers as you want for each operation, just go through number by number, and make each number the minimum you can with each operation.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int high = m;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = high;
		while(low <= high) {
			if(isValid(mid)) {
				ans = Math.min(ans, mid);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
