//package binaryliterature;

import java.util.*;
import java.io.*;

public class binaryliterature {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[][] s = new char[3][];
			int n = Integer.parseInt(fin.readLine());
			for(int i = 0; i < 3; i++) {
				s[i] = fin.readLine().toCharArray();
			}
			int p0 = 0;
			int p1 = 0;
			int p2 = 0;
			while(p0 != n * 2 && p1 != n * 2 && p2 != n * 2) {
				//System.out.println(s[0][p0] + " " + s[1][p1] + " " + s[2][p2]);
				if(s[0][p0] == s[1][p1] && s[1][p1] == s[2][p2]) {
					fout.append(s[0][p0]);
					p0 ++;
					p1 ++;
					p2 ++;
				}
				else if(s[0][p0] == s[1][p1]) {
					fout.append(s[0][p0]);
					p0 ++;
					p1 ++;
				}
				else if(s[1][p1] == s[2][p2]) {
					fout.append(s[1][p1]);
					p1 ++;
					p2 ++;
				}
				else if(s[0][p0] == s[2][p2]) {
					fout.append(s[2][p2]);
					p0 ++;
					p2 ++;
				}	
			}
			int p = 0;
			int which = 0;
			if(p0 == n * 2) {
				if(p1 >= p2) {
					p = p1;
					which = 1;
				}
				else {
					p = p2;
					which = 2;
				}
			}
			else if(p1 == n * 2) {
				if(p0 >= p2) {
					p = p0;
					which = 0;
				}
				else {
					p = p2;
					which = 2;
				}
			}
			else {
				if(p0 >= p1) {
					p = p0;
					which = 0;
				}
				else {
					p = p1;
					which = 1;
				}
			}
			for(int i = p; i < n * 2; i++) {
				fout.append(s[which][i]);
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
