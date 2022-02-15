//package yetanotherminimizationproblem;

import java.util.*;
import java.io.*;

public class yetanotherminimizationproblem {
	
	public static int swap(int[][] nums) {
		int swap = -1;
		int ans = 0;
		for(int i = 0; i < nums.length; i++) {
			for(int j = i + 1; j < nums.length; j++) {
				int a = i == swap? nums[i][1] : nums[i][0];
				int b = j == swap? nums[j][1] : nums[j][0];
				ans += Math.pow(a + b, 2);
			}
		}
		for(int i = 0; i < nums.length; i++) {
			for(int j = i + 1; j < nums.length; j++) {
				int a = i == swap? nums[i][0] : nums[i][1];
				int b = j == swap? nums[j][0] : nums[j][1];
				ans += Math.pow(a + b, 2);
			}
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1637D
		
		//you can simplify the cost function to make the problem into a problem of making the two arrays equal.
		
		//to make them equal, you can just do a 0 - 1 dp approach, using the differences between pairs of numbers as weights.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] nums = new int[n][2];
			int sum = 0;
			int aSum = 0;
			for(int i = 0; i < 2; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < n; j++) {
					nums[j][i] = Integer.parseInt(st.nextToken());
					sum += nums[j][i];
					aSum += i == 0? nums[j][i] : 0;
				}
			}
			boolean[] dp = new boolean[sum + 1];
			dp[aSum] = true;
			//System.out.println(aSum);
			for(int i = 0; i < n; i++) {
				int diff = nums[i][1] - nums[i][0];
				if(diff < 0) {
					for(int j = 0; j < dp.length; j++) {
						if(j + diff >= 0 && dp[j]) {
							dp[j + diff] = true;
							//System.out.println("YES " + (j + diff));
						}
					}
				}
				else {
					for(int j = sum; j >= 0; j--) {
						if(j + diff <= sum && dp[j]) {
							dp[j + diff] = true;
						}
					}
				}
			}
			int ans = Integer.MAX_VALUE;
			for(int i = 0; i < dp.length; i++) {
				if(dp[i]) {
					int curAns = i * i + (int) Math.pow(sum - i, 2);
					//System.out.println(i + " " + curAns);
					ans = Math.min(curAns, ans);
				}
			}
			//System.out.println(sum);
			int temp = 0;
			//System.out.println(ans);
			for(int[] i : nums) {
				temp += Math.pow(i[0], 2);
				temp += Math.pow(i[1], 2);
			}
			temp *= n - 2;
			ans += temp;
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
