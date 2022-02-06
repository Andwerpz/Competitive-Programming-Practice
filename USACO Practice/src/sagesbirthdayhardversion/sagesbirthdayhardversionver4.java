package sagesbirthdayhardversion;

import java.util.*;
import java.io.*;

public class sagesbirthdayhardversionver4 {
	
	public static boolean isValid(Integer[] nums, int val) {
		if(val == 0) {
			return true;
		}
		int h = nums.length - 2;
		int l = val - 1;
		while(true) {
			if(nums[h] <= nums[l]) {
				return false;
			}
			l --;
			h --;
			if(l == -1) {
				break;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1419D2
		
		//simple binary search + greedy 
		
		//binary search the maximum amount of ice spheres sage can purchase
		
		//when testing a given amount of spheres, it is obvious that you would want to designate the cheapest spheres to
		//buy, and the most expensive spheres to place around the cheap ones to classify them as 'cheap'. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		Integer[] nums = new Integer[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int high = n / 2;
		int low = 0;
		if(n % 2 == 0) {
			high --;
		}
		int mid = low + (high - low) / 2;
		int ans = 0;
		while(low <= high) {
			//System.out.println(mid);
			if(isValid(nums, mid)) {
				ans = Math.max(ans, mid);
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		//construct ans
		StringBuilder fout = new StringBuilder();
		fout.append(ans).append("\n");
		int h = nums.length - 2;
		int l = ans - 1;
		fout.append(nums[n - 1]).append(" ");
		while(h >= ans) {
			if(l >= 0) {
				fout.append(nums[l]).append(" ");
			}
			fout.append(nums[h]).append(" ");
			l --;
			h --;
			if(h < ans) {
				break;
			}
		}
		System.out.println(fout);
	}
}
