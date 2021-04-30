//package skyscraperseasyversion;

import java.util.*;
import java.io.*;

public class skyscraperseasyversion {
	public static void main(String[] args) throws IOException {
		
		//since there is always a peak, we just go around and set each plot as the "peak" and see how many floors we can get
		//take the maximum
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		long ans = 0;
		int[] ansArr = new int[n];
		for(int i = 0; i < n; i++) {
			long max = nums[i];
			int cur = nums[i];
			int[] curArr = new int[n];
			curArr[i] = (int) max;
			for(int j = i - 1; j >= 0; j --) {
				max += Math.min(cur, nums[j]);
				cur = Math.min(cur, nums[j]);
				curArr[j] = cur;
			}
			cur = nums[i];
			for(int j = i + 1; j < n; j++) {
				max += Math.min(cur, nums[j]);
				cur = Math.min(cur, nums[j]);
				curArr[j] = cur;
			}
			if(max > ans) {
				ansArr = curArr;
				ans = max;
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i : ansArr) {
			fout.append(i + " ");
		}
		//System.out.println(ans);
		System.out.println(fout);
	}
}
