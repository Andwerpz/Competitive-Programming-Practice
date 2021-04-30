package byelevatororstairs;

import java.util.*;
import java.io.*;

public class byelevatororstairsver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int[] stairs = new int[n - 1];
		int[] elevator = new int[n - 1];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n - 1; i++) {
			stairs[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n - 1; i++) {
			elevator[i] = Integer.parseInt(st.nextToken());
		}
		long[][] dp = new long[n][2];	//the min cost to get to floor i, with two options, stairs or elevator, 0 or 1.
		dp[0][0] = 0;
		dp[0][1] = c;	//initial cost of elevator
		StringBuilder fout = new StringBuilder();
		fout.append("0 ");
		for(int i = 1; i < n; i++) {
			dp[i][0] = Math.min(dp[i - 1][0] + stairs[i - 1], dp[i - 1][1] + stairs[i - 1]);
			dp[i][1] = Math.min(dp[i - 1][1] + elevator[i - 1], dp[i - 1][0] + elevator[i - 1] + c);
			fout.append(Math.min(dp[i][0], dp[i][1])).append(" ");
		}
		System.out.println(fout);
	}
}
