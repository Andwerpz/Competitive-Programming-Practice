//package constantpalindromesum;

import java.util.*;
import java.io.*;

public class constantpalindromesum {
	public static void main(String[] args) throws IOException {
		
		//1343D
		
		//use prefix sum to solve this problem. For each number pair, mark out the ranges of k in which you'll need 0, 1 or 2 moves to make the sum equal to that k. Repeat
		//for all number pairs, and then iterate through all values of k to find the minimum.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int[] pfx = new int[k * 2 + 1];
			for(int i = 0; i < n / 2; i++) {
				int a = nums[i];
				int b = nums[n - 1 - i];
				int min = Math.min(a, b) + 1;
				int max = Math.max(a, b) + k;
				pfx[0] += 2;
				pfx[min - 1] -= 2;
				pfx[min - 1] += 1;
				pfx[max] -= 1;
				pfx[max] += 2;
				pfx[a + b - 1] -= 1;
				pfx[a + b] += 1;
//				for(int j : pfx) {
//					System.out.print(j + " ");
//				}
//				System.out.println();
			}
			int min = Integer.MAX_VALUE;
			for(int i = 1; i < pfx.length; i++) {
				//System.out.print(pfx[i - 1] + " ");
				min = Math.min(min, pfx[i - 1]);
				pfx[i] += pfx[i - 1];
			}
			fout.append(min).append("\n");
		}
		System.out.print(fout);
	}
}
