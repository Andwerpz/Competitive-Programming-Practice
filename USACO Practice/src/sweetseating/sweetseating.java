//package sweetseating;

import java.util.*;
import java.io.*;

public class sweetseating {
	public static void main(String[] args) throws IOException {
		
		//1253C
		
		//you are given n sweets, each with a unique sweetness. if you eat the sweet with sweetness a on day d, then the sweetness penalty for that sweet is going to be
		//a * d. You can eat a maximum of k sweets on each day. print the minimum sweetness penalty you can accrue if you eat for each 1 - n sweets.
		//given a number of sweets, it is optimal to eat the most sweets sweets in the first days, and save the least sweet ones for the last days. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		long[] nums = new long[n];
		long[] pfx = new long[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		for(int i = 0; i < n; i++) {
			long next = nums[i];
			if(i < m) {
				pfx[i] = next;
			}
			else {
				pfx[i] = next + pfx[i - m];
			}
		}
		StringBuilder fout = new StringBuilder();
		long sum = 0;
		for(int i = 0; i < n; i++) {
			sum += pfx[i];
			fout.append(sum).append(" ");
		}
		System.out.println(fout);
	}
}
