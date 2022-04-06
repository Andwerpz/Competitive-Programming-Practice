//package missingcoinsum;

import java.util.*;
import java.io.*;

public class missingcoinsum {
	public static void main(String[] args) throws IOException {
		
		//CSES 2183
		
		//first sort the coins in ascending order
		
		//consider the ith coin. var sum represents the sum of coins from 0 - i.
		
		//assume that the first i coins can make any value between 0 - sum. If the next coin is greater than sum + 1, then 
		//it is impossible to make sum + 1, but if it is less than or equal to sum + 1, it is possible to make everything
		//from 0 - (sum + next) using the next coin. 
		
		//if we start from the lowest value coin, then the assumption that the first i coins can make values 0 - sum is true when 
		//the smallest coin == 1. 
		
		Kattio cin = new Kattio();
		int n = cin.nextInt();
		Long[] nums = new Long[n];
		for(int i = 0; i < n; i++) {
			nums[i] = cin.nextLong();
		}
		Arrays.sort(nums);
		long sum = 0;
		long ans = -1;
		for(int i = 0; i < n; i++) {
			long next = nums[i];
			if(sum < next - 1) {
				ans = sum + 1;
				break;
			}
			sum += next;
		}
		if(ans == -1) {
			ans = sum + 1;
		}
		System.out.println(ans);
		cin.close();
	}
	
	static class Kattio extends PrintWriter {
		private BufferedReader r;
		private StringTokenizer st;
		// standard input
		public Kattio() { this(System.in, System.out); }
		public Kattio(InputStream i, OutputStream o) {
			super(o);
			r = new BufferedReader(new InputStreamReader(i));
		}
		// USACO-style file input
		public Kattio(String problemName) throws IOException {
			super(problemName + ".out");
			r = new BufferedReader(new FileReader(problemName + ".in"));
		}
		// returns null if no more input
		public String next() {
			try {
				while (st == null || !st.hasMoreTokens())
					st = new StringTokenizer(r.readLine());
				return st.nextToken();
			} catch (Exception e) { }
			return null;
		}
		public int nextInt() { return Integer.parseInt(next()); }
		public double nextDouble() { return Double.parseDouble(next()); }
		public long nextLong() { return Long.parseLong(next()); }
	}
}
