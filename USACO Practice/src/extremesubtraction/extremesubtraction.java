//package extremesubtraction;

import java.util.*;
import java.io.*;

public class extremesubtraction {
	
	public static boolean isValid(int[] nums) {
		int pointer = nums[0];
		nums[0] = 0;
		for(int i = 1; i < nums.length - 1; i++) {
			int diff = Math.abs(nums[i - 1] - nums[i]);
			nums[i] -= Math.min(pointer, diff);
			pointer = Math.min(pointer, diff);
			if(nums[i + 1] < nums[i]) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1442A
		
		//you want to see whether if you remove a non-increasing prefix from the nums array, that a non-increasing suffix will remain. To test this, you can walk along the array, removing as much as 
		//you can at that point, which is going to be the minimum of all the stuff that you removed so far.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			fout.append(isValid(nums)? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
