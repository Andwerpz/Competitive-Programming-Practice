//package vacations;

import java.util.*;
import java.io.*;

public class vacations {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int ans = 0;
		boolean[][] dp = new boolean[n][2];	//dp[j][i]; whether or not he can do i, 0; gym, 1; contest, on day j.
		for(int i = 0; i < n; i++) {
			if(i == 0) {
				if(nums[i] == 0) {	//both are closed
					
				}
				else if(nums[i] == 1) {	//gym closed, contest is done
					dp[0][1] = true;
				}
				else if(nums[i] == 2) {	//gym done, contest closed
					dp[0][0] = true;
				}
				else {	//both done
					dp[0][0] = true;
					dp[0][1] = true;
				}
			}
			else {
				if(nums[i] != 0) {	//if it is not a rest day
					if(dp[i - 1][1] == false && nums[i] != 0 && nums[i] != 2) {
						dp[i][1] = true;
					}
					if(dp[i - 1][0] == false && nums[i] != 0 && nums[i] != 1) {
						dp[i][0] = true;
					}
					if((dp[i - 1][0] || nums[i - 1] == 0) && nums[i] != 2) {	//we did gym yesterday, we're doing the contest today
						dp[i][1] = true;
					}
					if((dp[i - 1][1] || nums[i - 1] == 0) && nums[i] != 1) {	//did contest yesterday, doing gym today
						dp[i][0] = true;
					}
				}
			}
			//System.out.println(dp[i][0] + " " + dp[i][1]);
			if(!(dp[i][0] || dp[i][1])) {
				ans ++;
			}
		}
		System.out.println(ans);
	}
}
