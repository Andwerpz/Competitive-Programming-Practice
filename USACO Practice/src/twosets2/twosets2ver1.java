package twosets2;

import java.util.*;
import java.io.*;

public class twosets2ver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		HashMap<Long, Long> dp = new HashMap<Long, Long>();
		int mod = 1000000007;
		long sum = 0;
		for(int i = 1; i <= n; i++) {
			sum += i;
		}System.out.println(sum / 2);
		if(sum % 2 == 1) {
			System.out.println("0");
		}
		
		else {
			for(long i = 1; i <= n; i++) {
				Set<Long> keys = dp.keySet();
				HashMap<Long, Long> next = new HashMap<Long, Long>();
				for(long k : keys) {
					if(k + i <= sum / 2) {
						next.put(k + i, (dp.get(k) + next.getOrDefault(k + i, (long) 0)) % mod);
					}
				}
				dp.put(i, dp.getOrDefault(i, (long) 0) + 1);
				Set<Long> nextKeys = next.keySet();
				for(long k : nextKeys) {
					dp.put(k, (dp.getOrDefault(k, (long) 0) + next.get(k)) % mod);
				}
			}
			System.out.println(dp.get((long)sum / 2) / 2);
		}
	}
}
