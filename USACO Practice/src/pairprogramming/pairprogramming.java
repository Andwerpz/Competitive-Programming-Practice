//package pairprogramming;

import java.util.*;
import java.io.*;

public class pairprogramming {
	public static void main(String[] args) throws IOException {
		
		//1547C
		
		//we can use a greedy approach: whenever we can change a line, we should change it, otherwise we should add more lines. Honestly, it doesn't matter in what order you do the
		//steps. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int k = Integer.parseInt(st.nextToken());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[] mono = new int[n];
			int[] poly = new int[m];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				mono[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				poly[i] = Integer.parseInt(st.nextToken());
			}
			int pm = 0;
			int pp = 0;
			int pointer = 0;
			int[] ans = new int[n + m];
			boolean isValid = true;
			while(pm < n || pp < m) {
				if(pm < n && mono[pm] <= k) {
					if(mono[pm] == 0) {
						k ++;
					}
					ans[pointer] = mono[pm];
					pointer ++;
					pm ++;
				}
				else if(pp < m && poly[pp] <= k) {
					if(poly[pp] == 0) {
						k ++;
					}
					ans[pointer] = poly[pp];
					pointer ++;
					pp ++;
					
				}
				else {
					isValid = false;
					break;
				}
			}
			if(isValid) {
				for(int i = 0; i < ans.length; i++) {
					fout.append(ans[i]).append(" ");
				}
				fout.append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
