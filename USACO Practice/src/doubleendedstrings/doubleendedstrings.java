//package doubleendedstrings;

import java.util.*;
import java.io.*;

public class doubleendedstrings {
	public static void main(String[] args) throws IOException {
		//brute force lol
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			char[] a = fin.readLine().toCharArray();
			char[] b = fin.readLine().toCharArray();
			int max = 0;
			for(int i = 0; i < a.length; i++) {
				for(int j = 0; j < b.length; j++) {
					if(a[i] == b[j]) {
						int cur = 0;
						int aPoint = i;
						int bPoint = j;
						while(aPoint < a.length && bPoint < b.length && a[aPoint] == b[bPoint]) {
							aPoint ++;
							bPoint ++;
							cur ++;
						}
						max = Math.max(cur, max);
					}
				}
			}
			fout.append((a.length + b.length) - max * 2).append("\n");
		}
		System.out.print(fout);
	}
}
