//package dreamoonlikessequences;

import java.util.*;
import java.io.*;

public class dreamoonlikessequences {
	public static void main(String[] args) throws IOException {
		
		//1329B
		
		//arrays a and b must both be increasing. b must be prefix xor of a. The only way to satisfy both conditions is for every consecutive number of a to be 
		//higher than the next by a power of 2. Make pools, and do some combination math
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int d = Integer.parseInt(st.nextToken());
			long mod = Integer.parseInt(st.nextToken());
			int numPools = (int) (Math.floor(Math.log(d) / Math.log(2))) + 1;
			long[] poolAmount = new long[numPools];
			for(int i = 0; i < numPools - 1; i++) {
				poolAmount[i] = (long) Math.pow(2, i);
			}
			poolAmount[numPools - 1] = d - (long) (Math.pow(2, numPools - 1)) + 1;
			//System.out.println(Math.pow(2, numPools - 1));
			long ans = 0;
			long[][] dp = new long[numPools][numPools];
			for(int i = 0; i < numPools; i++) {
				for(int j = 0; j < numPools - i; j++) {
					if(i == 0) {
						ans += poolAmount[j];
						ans %= mod;
						dp[i][j] = poolAmount[j];
						dp[i][j] %= mod;
					}
					else {
						long cur = poolAmount[j];
						for(int k = j + 1; k < numPools; k++) {
							ans += cur * dp[i - 1][k];
							ans %= mod;
							dp[i][j] += cur * dp[i - 1][k];
							dp[i][j] %= mod;
						}
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
