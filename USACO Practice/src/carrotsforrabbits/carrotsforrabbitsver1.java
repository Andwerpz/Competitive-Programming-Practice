//package carrotsforrabbits;

import java.util.*;
import java.io.*;	

public class carrotsforrabbitsver1 {
	public static void main(String[] args) throws IOException {
		
		//1428E
		
		//not correct solution, we can't just greedily reduce numbers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		TreeMap<Long, Long> dict = new TreeMap<Long, Long>();
		for(int i = 0; i < n; i++) {
			long next = Integer.parseInt(st.nextToken());
			dict.put(next, dict.getOrDefault(next, (long) 0) + 1);
		}
		int total = n;
		while(total != k) {
			long next = dict.lastKey();
			long nextAmt = dict.get(next);
			long diff = Math.min(nextAmt, Math.abs(k - total));
			total += diff;
			dict.put(next, nextAmt - diff);
			if(dict.get(next) == 0) {
				dict.remove(next);
			}
			if(next % 2 == 0) {
				dict.put(next / 2, dict.getOrDefault(next / 2, 0l) + nextAmt * 2);
			}
			else {
				dict.put(next / 2, dict.getOrDefault(next / 2, 0l) + nextAmt);
				dict.put(next / 2 + 1, dict.getOrDefault(next / 2 + 1, 0l) + nextAmt);
			}
		}
		long ans = 0;
		for(long i : dict.keySet()) {
			long nextSum = i * i * dict.get(i);
			ans += nextSum;
		}
		System.out.println(ans);
	}
}
