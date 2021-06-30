//package codeforcessubsequences;

import java.util.*;
import java.io.*;

public class codeforcessubsequences {
	
	public static long getVal(long[] nums) {
		long val = 1;
		for(int i = 0; i < nums.length; i++) {
			val *= nums[i];
		}
		return val;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1368B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long k = Long.parseLong(fin.readLine());
		long[] nums = new long[10];
		Arrays.fill(nums, 1);
		int pointer = 0;
		while(getVal(nums) < k) {
			nums[pointer % 10] ++;
			pointer ++;
		}
		char[] s = "codeforces".toCharArray();
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < nums[i]; j++) {
				fout.append(s[i]);
			}
		}
		System.out.println(fout);
	}
}
