//package densearray;

import java.util.*;
import java.io.*;

public class densearray {
	public static void main(String[] args) throws IOException {
		
		//1490A
		
		//just simulate adding numbers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int ans = 0;
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			for(int i = 1; i < n; i++) {
				int small = Math.min(nums[i], nums[i - 1]);
				int big = Math.max(nums[i], nums[i - 1]);
				while(small * 2 < big) {
					small *= 2;
					ans ++;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
