//package greenhouseeffect;

import java.util.*;
import java.io.*;

public class greenhouseeffect {
	public static void main(String[] args) throws IOException {
		
		//find the longest non decreasing subset. Move all other plants
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int[] dp = new int[n];	//at position i, saves the smallest ending value of a non decreasing subsequence with i members.
		Arrays.fill(dp, Integer.MAX_VALUE);
		int max = 0;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			int pointer = 0;
			while(dp[pointer] <= next) {
				pointer ++;
			}
			dp[pointer] = Math.min(next, dp[pointer]);
			max = Math.max(max, pointer);
		}
		System.out.println(n - max - 1);
	}
}
