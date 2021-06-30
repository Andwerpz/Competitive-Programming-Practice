//package binaryliterature;

import java.util.*;
import java.io.*;

public class binaryliteraturever1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		int counter = 0;
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			counter ++;
			int n = Integer.parseInt(fin.readLine());
			char[][] s = new char[3][];
			for(int i = 0; i < 3; i++) {
				s[i] = fin.readLine().toCharArray();
			}
			boolean done = false;
			for(int i = 0; i < 2; i++) {
				for(int j = i + 1; j < 3; j++) {
					StringBuilder cur = new StringBuilder();
					int b = 0;
					for(int k = 0; k < n * 2; k++) {
						if(s[i][k] == s[j][b]) {
							b ++;
						}
						cur.append(s[i][k]);
					}
					for(int k = b; k < n * 2; k++) {
						cur.append(s[j][k]);
					}
					if(cur.length() <= n * 3) {
						fout.append(cur).append("\n");
						done = true;
						break;
					}
					cur = new StringBuilder();
					b = 0;
					for(int k = 0; k < n * 2; k++) {
						if(s[i][b] == s[j][k]) {
							b ++;
						}
						cur.append(s[j][k]);
					}
					for(int k = b; k < n * 2; k++) {
						cur.append(s[i][k]);
					}
					if(cur.length() <= n * 3) {
						fout.append(cur).append("\n");
						done = true;
						break;
					}
					cur = new StringBuilder();
					for(int k = 0; k < n * 2; k++) {
						if(s[i][k] == s[j][k]) {
							cur.append(s[i][k]);
						}
						else {
							cur.append("01");
						}
					}
					if(cur.length() <= n * 3) {
						fout.append(cur).append("\n");
						done = true;
						break;
					}
				}
				if(done) {
					break;
				}
			}
			
			if(!done) {
				fout.append("couldn't find one\n");
			}
		}
		System.out.print(fout);
	}
}
