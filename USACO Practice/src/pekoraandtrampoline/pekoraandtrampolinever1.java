package pekoraandtrampoline;

import java.util.*;
import java.io.*;

public class pekoraandtrampolinever1 {
	public static void main(String[] args) throws IOException {
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
			boolean done = false;
			int ans = 0;
			while(!done) {
				done = true;
				int[] dp = new int[n];
				for(int i = n - 1; i >= 0; i--) {
					if(nums[i] > 1) {
						dp[i] ++;
					}
					if(i + nums[i] < n) {
						dp[i] += dp[i + nums[i]];
					}
				}
				int max = 0;
				int index = 0;
				for(int i = 0; i < n; i++) {
					if(dp[i] > max) {
						done = false;
						max = dp[i];
						index = i;
					}
				}
				if(done) {
					break;
				}
				else {
					for(int i : dp) {
						System.out.print(i + " ");
					}
					System.out.println();
					for(int i : nums) {
						System.out.print(i + " ");
					}
					System.out.println();
					System.out.println();
					ans ++;
					while(index < n) {
						int temp = nums[index];
						if(nums[index] > 1) {
							nums[index] --;
						}
						index += temp;
					}
					
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
