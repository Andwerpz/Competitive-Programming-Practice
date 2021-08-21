//package saynotopalindromes;

import java.util.*;
import java.io.*;

public class saynotopalindromes {
	public static void main(String[] args) throws IOException {
		
		//1555D
		
		//a string s that doesn't have any palindromes must be 1 of 6 cyclic patterns. Just try to match s to each pattern, and record a pfx sum of wrong characters, so you can answer
		//queries in O(1)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		char[][] order = new char[][] {{'a', 'b', 'c'}, {'b', 'c', 'a'}, {'c', 'a', 'b'}, {'c', 'b', 'a'}, {'b', 'a', 'c'}, {'a', 'c', 'b'}};
		int[][] pfx = new int[n][6];
		for(int i = 0; i < n; i++) {
			char cur = s[i];
			for(int j = 0; j < 6; j++) {
				if(cur != order[j][i % 3]) {
					pfx[i][j] ++;
				}
				if(i != 0) {
					pfx[i][j] += pfx[i - 1][j];
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			int ans = Integer.MAX_VALUE;
			for(int j = 0; j < 6; j++) {
				ans = Math.min(ans, pfx[r][j] - (l == 0? 0 : pfx[l - 1][j]));
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
