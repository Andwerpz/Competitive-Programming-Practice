package geometricprogression;

import java.util.*;
import java.io.*;

public class geometricprogressionver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		HashMap<Long, Long> dict = new HashMap<Long, Long>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		long[] nums = new long[n];
		long[] dp = new long[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = n - 1; i >= 0; i--) {
			long next = nums[i];
			if(dict.containsKey(next * k)) {
				dp[i] = dict.get(next * k);
			}
			dict.put(next, dict.getOrDefault(next, (long) 0) + 1);
		}
		long ans = 0;
		for(int i = 0; i < n; i++) {
			long a = nums[i];
			long b = a * k;
			long c = b * k;
			if(dict.containsKey(a) && dict.containsKey(b) && dict.containsKey(c)) {
				ans += dp[i];
			}
		}
		System.out.println(ans);
	}
}
