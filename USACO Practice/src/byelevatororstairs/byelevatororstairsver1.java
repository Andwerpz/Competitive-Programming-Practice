package byelevatororstairs;

import java.util.*;
import java.io.*;

public class byelevatororstairsver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken()) - 1;
		int c = Integer.parseInt(st.nextToken());
		int[] stairs = new int[n];
		int[] elevator = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			stairs[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			elevator[i] = Integer.parseInt(st.nextToken());
		}
		long[] dp = new long[n + 1];	//the minimum cost required to get to the ith floor.
		dp[0] = 0;
		boolean ele = false;
		for(int i = 1; i <= n; i++) {
			long withEle = dp[i - 1] + (ele? 0 : c) + elevator[i - 1];
			long noEle = dp[i - 1] + stairs[i - 1];
			if(withEle <= noEle) {
				dp[i] = withEle;
				ele = true;
			}
			else {
				dp[i] = noEle;
				ele = false;
			}
		}
		StringBuilder fout = new StringBuilder();
		for(long i : dp) {
			fout.append(i + " ");
		}
		System.out.println(fout);
	}
}
