//package sequenceandswaps;

import java.util.*;
import java.io.*;

public class sequenceandswaps {
	
	public static boolean sorted(int[] nums) {
		int prev = nums[0];
		for(int i = 1; i < nums.length; i++) {
			if(nums[i] < prev) {
				return false;
			}
			prev = nums[i];
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1455D
		
		//notice that if all numbers that are less than x are sorted, then you can sort all of the numbers by iterating down the array and swapping numbers whenever you can.
		//to get the minimum amount of swaps, before each time you swap, just check whether its sorted or not, and if it's sorted, return the current amount of swaps.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			boolean isValid = false;
			int ans = 0;
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			for(int i = 0; i < n; i++) {
				if(sorted(nums)) {
					isValid = true;
					break;
				}
				if(nums[i] > x) {
					int temp = x;
					x = nums[i];
					nums[i] = temp;
					ans ++;
				}
			}
			if(sorted(nums)) {
				isValid = true;
			}
			if(isValid) {
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");
			}
			
		}
		System.out.print(fout);
	}
}
