//package twosets2;

import java.util.*;
import java.io.*;

public class twosets2ver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		int mod = 1000000007;
		int sum = 0;
		for(int i = 1; i <= n; i++) {
			sum += i;
		}
		if(sum % 2 == 1) {
			System.out.println("0");
		}
		else {
			int target = sum / 2;
			int[][] dp = new int[n][target + 1];
			dp[0][0] = 1;
			for(int i = 1; i < n; i++) {
				for(int j = 0; j < dp[i].length; j++) {
					if(j - i >= 0) {
						dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - i]) % mod;	//either we add the current number, or we don't
					}
					else {
						dp[i][j] = dp[i - 1][j];	//in this case, we can't add the current number
					}
					
					//System.out.print(dp[i][j] + " ");
				}
				//System.out.println();
			}
			System.out.println(dp[n - 1][target]);
		}
	}
}
