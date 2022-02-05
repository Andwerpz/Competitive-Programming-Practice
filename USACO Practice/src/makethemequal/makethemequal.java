//package makethemequal;

import java.util.*;
import java.io.*;

public class makethemequal {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		//precompute number of operations required to get to each number
		int[] dict = new int[1001];
		Arrays.fill(dict, -1);
		dict[1] = 0;
		for(int i = 1; i < dict.length; i++) {
			for(int j = 1; j <= i; j++) {
				int nextOps = dict[i] + 1;
				int nextNum = i + (i / j);
				if(nextNum <= 1000) {
					dict[nextNum] = dict[nextNum] == -1? nextOps : Math.min(nextOps, dict[nextNum]);
				}
			}
		}
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Math.min(n * 12, Integer.parseInt(st.nextToken()));
			st = new StringTokenizer(fin.readLine());
			int[] b = new int[n];
			int[] c = new int[n];
			for(int i = 0; i < n; i++) {
				b[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				c[i] = Integer.parseInt(st.nextToken());
			}
			int[] dp = new int[k + 1];	//amount of operations used : maximum coins
			Arrays.fill(dp, -1);
			int ans = 0;
			dp[0] = 0;
			for(int i = 0; i < n; i++) {
				int cost = dict[b[i]];
				int value = c[i];
				for(int j = k; j >= 0; j--) {
					if(dp[j] != -1 && j + cost <= k) {
						dp[j + cost] = Math.max(dp[j + cost], dp[j] + value);
						ans = Math.max(ans, dp[j + cost]);
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
