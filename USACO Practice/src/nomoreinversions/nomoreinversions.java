//package nomoreinversions;

import java.util.*;
import java.io.*;

public class nomoreinversions {
	public static void main(String[] args) throws IOException { 
		
		//1473C
		
		//maths
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int numReversed = Math.abs(n - k) + 1;
			if(n == 1) {
				numReversed = 0;
			}
			int[] ans = new int[k];
			int pointer = 1;
			while(pointer <= k - numReversed) {
				ans[pointer - 1] = pointer;
				pointer ++;
			}
			if(ans.length != 1) {
				for(int i = ans.length - 1; i > ans.length - 1 - numReversed; i--) {
					ans[i] = pointer;
					pointer ++;
				}
			}
			
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
