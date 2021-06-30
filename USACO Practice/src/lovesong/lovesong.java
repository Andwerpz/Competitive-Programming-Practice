//package lovesong;

import java.util.*;
import java.io.*;

public class lovesong {
	public static void main(String[] args) throws IOException {
		
		//1539B
		
		//construct a pfx sum array. a = 1, b = 2 ... z = 26. When answering the queries, just return the subarray sum between l and r inclusive.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		int[] pfx = new int[n];
		for(int i = 0; i < n; i++) {
			pfx[i] = s[i] - ('a' - 1);
			if(i != 0) {
				pfx[i] += pfx[i - 1];
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken()) - 2;
			int r = Integer.parseInt(st.nextToken()) - 1;
			fout.append((pfx[r] - (l == -1? 0 : pfx[l]))).append("\n");
		}
		System.out.print(fout);
	}
}
