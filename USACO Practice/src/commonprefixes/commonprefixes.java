//package commonprefixes;

import java.util.*;
import java.io.*;

public class commonprefixes {
	public static void main(String[] args) throws IOException {
		
		//1384A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] prev = new char[50];
			for(int i = 0; i < prev.length; i++) {
				prev[i] = 'a';
			}
			fout.append(String.valueOf(prev)).append("\n");
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				char[] cur = new char[50];
				for(int j = 0; j < next; j++) {
					cur[j] = prev[j];
				}
				for(int j = next; j < cur.length; j++) {
					cur[j] = 'a';
					if(cur[j] == prev[j]) {
						cur[j] = 'b';
					}
				}
				fout.append(String.valueOf(cur)).append("\n");
				prev = cur;
			}
		}
		System.out.print(fout);
	}
}
