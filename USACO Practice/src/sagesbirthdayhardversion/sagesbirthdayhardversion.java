//package sagesbirthdayhardversion;

import java.util.*;
import java.io.*;

public class sagesbirthdayhardversion {
	
	public static boolean isValid(int val, int[] nums) {
		if(val + val + 1 > nums.length) {
			return false;
		}
		else if(val == 0) {
			return true;
		}
		if(nums[val - 1] < nums[nums.length - 1 - val]) {
			return true;
		}
		return false;
	}
	
	public static StringBuilder getAns(int val, int[] nums) {
		StringBuilder fout = new StringBuilder();
		int pointer = nums.length - 1;
		for(int i = 0; i < val; i++) {
			fout.append(nums[pointer]).append(" ").append(nums[i]).append(" ");
			pointer --;
		}
		for(int i = pointer; i >= val; i--) {
			fout.append(nums[i]).append(" ");
		}
		fout.append("\n");
		return fout;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1419D2
		
		//do binary search 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int high = nums.length;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = low;
		while(low <= high) {
			if(isValid(mid, nums)) {
				ans = Math.max(ans, mid);
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
		System.out.print(getAns(ans, nums));
	}
}
