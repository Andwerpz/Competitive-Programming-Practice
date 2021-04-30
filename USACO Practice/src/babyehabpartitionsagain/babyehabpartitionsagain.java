//package babyehabpartitionsagain;

import java.util.*;
import java.io.*;

public class babyehabpartitionsagain {
	public static void main(String[] args) throws IOException {
		
		//odd sums mean that the arr is good.
		//if sum is even, then div arr by 2
		//remove odd number
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int sum = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
		}
		int ans = 0;
		if(sum % 2 == 1) {	//arr is already good
			System.out.println("0");
		}
		else {
			boolean[] dp = new boolean[sum + 1];
			dp[0] = true;
			for(int i = 0; i < n; i++) {
				for(int j = dp.length - 1; j >= 0; j--) {
					if(dp[j]) {
						dp[j + nums[i]] = true;
					}
				}
			}
			if(!dp[sum / 2]) {	//arr is already good
				System.out.println("0");
			}
			else {
				ans = 0;
				boolean done = false;
				while(true) {
					for(int i = 0; i < n; i++) {
						if(nums[i] % 2 == 1) {	//remove odd number
							ans = i + 1;
							done = true;
							break;
						}
						else {
							nums[i] /= 2;
						}
					}
					if(done) {
						break;
					}
				}
				System.out.println("1\n" + ans);
			}
		}
	}
}
