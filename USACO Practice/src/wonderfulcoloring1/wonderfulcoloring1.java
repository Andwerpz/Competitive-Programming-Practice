//package wonderfulcoloring1;

import java.util.*;
import java.io.*;

public class wonderfulcoloring1 {
	public static void main(String[] args) throws IOException {
		
		//1551B1
		
		//Separate the letters into groups of 2 or more, and groups of 1. Combine 2 unique letters to form a 2 group.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int[] dict = new int[26];
			for(int i = 0; i < s.length; i++) {
				int next = s[i] - 'a';
				dict[next] ++;
			}
			int ans = 0;
			boolean extra = false;
			for(int i = 0; i < dict.length; i++) {
				if(dict[i] >= 2) {
					ans ++;
				}
				else if(dict[i] == 1) {
					if(extra) {
						ans ++;
						extra = false;
					}
					else {
						extra = true;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
