//package convolutedintervals;

import java.util.*;
import java.io.*;

public class convolutedintervals {
	public static void main(String[] args) throws IOException {
		
		//USACO 2021 December Contest Silver
		
		//prefix sums
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[][] intervals = new int[n][2];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			intervals[i][0] = Integer.parseInt(st.nextToken());
			intervals[i][1] = Integer.parseInt(st.nextToken());
		}
		long[] starts = new long[m + 1];
		long[] ends = new long[m + 1];
		long[] ans = new long[2 * m + 1];
		for(int i = 0; i < n; i++) {
			starts[intervals[i][0]] ++;
			ends[intervals[i][1]] ++;
		}
		for(int i = 0; i < starts.length; i++) {
			long startVal = starts[i];
			long endVal = ends[i];
			for(int j = 0; j < starts.length; j++) {
				ans[j + i] += starts[j] * startVal;
				if(j + i + 1 < ans.length) {
					ans[j + i + 1] += -ends[j] * endVal;
				}
			}
		}
		for(int i = 1; i < ans.length; i++) {
			//System.out.print(ans[i] + " ");
			ans[i] += ans[i - 1];
		}
		//System.out.println();
		StringBuilder fout = new StringBuilder();
		for(long i : ans) {
			fout.append(i).append("\n");
		}
		System.out.print(fout);
	}
}
