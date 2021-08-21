//package boboniuchatswithdu;

import java.util.*;
import java.io.*;

public class boboniuchatswithduver1 {
	public static void main(String[] args) throws IOException {
		
		//gets WA
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		long m = Integer.parseInt(st.nextToken());
		ArrayList<Long> small = new ArrayList<Long>();
		ArrayList<Long> large = new ArrayList<Long>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			long next = Integer.parseInt(st.nextToken());
			if(next <= m) {
				small.add(next);
			}
			else {
				large.add(next);
			}
		}
		small.sort((a, b) -> -Long.compare(a, b));
		large.sort((a, b) -> -Long.compare(a, b));
		long[][] dp = new long[n][3];
		long ans = 0;
		for(int i = 0; i < n; i++) {
			int sp = (int) dp[i][1];
			int lp = (int) dp[i][2];
			long curSum = dp[i][0];
			if(sp < small.size()) {
				ans = Math.max(ans, curSum + small.get(sp));
			}
			if(lp < large.size()) {
				ans = Math.max(ans, curSum + large.get(lp));
			}
			if(sp < small.size() && i + 1 < n && dp[i + 1][0] <= curSum + small.get(sp)) {
				dp[i + 1][0] = curSum + small.get(sp);
				dp[i + 1][1] = sp + 1;
				dp[i + 1][2] = lp;
			}
			if(lp < large.size() && i + d + 1 < n && dp[i + d + 1][0] < curSum + large.get(lp)) {
				dp[i + d + 1][0] = curSum + large.get(lp);
				dp[i + d + 1][1] = sp;
				dp[i + d + 1][2] = lp + 1;
			}
			//System.out.print(dp[i][0] + " ");
		}
		System.out.println(ans);
	}
}
