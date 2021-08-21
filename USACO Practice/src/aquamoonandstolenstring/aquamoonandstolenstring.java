//package aquamoonandstolenstring;

import java.util.*;
import java.io.*;

public class aquamoonandstolenstring {
	public static void main(String[] args) throws IOException {
		
		//1546B
		
		//to solve this, just count the occurrences of characters for each position for the initial and the end. Then go through each position, wherever there is a difference in number of characters, 
		//that's the character of the stolen string at that position.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] before = new int[m][26];
			int[][] after = new int[m][26];
			for(int i = 0; i < n; i++) {
				char[] next = fin.readLine().toCharArray();
				for(int j = 0; j < m; j++) {
					int index = next[j] - 'a';
					before[j][index] ++;
				}
			}
			for(int i = 0; i < n - 1; i++) {
				char[] next = fin.readLine().toCharArray();
				for(int j = 0; j < m; j++) {
					int index = next[j] - 'a';
					after[j][index] ++;
				}
			}
			for(int i = 0; i < m; i++) {
				for(int j = 0; j < 26; j++) {
					if(before[i][j] > after[i][j]) {
						fout.append((char) ('a' + j));
						break;
					}
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
