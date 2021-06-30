package foreigncurrency;

import java.util.*;
import java.io.*;

public class foreigncurrency {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int p = Integer.parseInt(st.nextToken());
		int[] dp = new int[p + 1];
		Arrays.fill(dp, -1);
		dp[0] = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			for(int j = 0; j <= p; j++) {
				if(dp[j] != -1 && next + j <= p) {
					if(dp[j + next] == -1) {
						dp[j + next] = dp[j] + 1;
					}
					else {
						dp[j + next] = Math.min(dp[j + next], dp[j] + 1);
					}
				}
			}
		}
		System.out.println(dp[p]);
	}
}
