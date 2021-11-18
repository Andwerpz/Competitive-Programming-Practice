//package dominantcharacter;

import java.util.*;
import java.io.*;

public class dominantcharacter {
	public static void main(String[] args) throws IOException {
		
		//1605C
		
		//you just have to narrow the situation down. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			boolean done = false;
			//first check if there are two adjacent 'a's. 
			int prevA = -2;
			for(int i = 0; i < n; i++) {
				char next = s[i];
				if(next == 'a') {
					if(prevA + 1 == i) {
						done = true;
						break;
					}
					prevA = i;
				}
			}
			if(done) {
				fout.append("2\n");
				continue;
			}
			//next, check if there is a 'b' or 'c' sandwiched between two 'a's. 
			for(int i = 2; i < n; i++) {
				char prev = s[i - 2];
				char next = s[i];
				if(next == 'a' && prev == 'a') {
					done = true;
					break;
				}
			}
			if(done) {
				fout.append("3\n");
				continue;
			}
			//check if there is a set of b and c between two 'a's. 
			for(int i = 3; i < n; i++) {
				char cur = s[i];
				char prev = s[i - 3];
				char a = s[i - 1];
				char b = s[i - 2];
				if(cur == 'a' && prev == 'a' && (a == 'b' || a == 'c') && (b == 'b' || b == 'c') && a != b) {
					done = true;
					break;
				}
			}
			if(done) {
				fout.append("4\n");
				continue;
			}
			//last, check if there is a structure like this: 'abbacca'
			for(int i = 6; i < n; i++) {
				char a1 = s[i];
				char a2 = s[i - 3];
				char a3 = s[i - 6];
				if(a1 == 'a' && a2 == 'a' && a3 == 'a') {
					char b1 = s[i - 1];
					char b2 = s[i - 2];
					char c1 = s[i - 4];
					char c2 = s[i - 5];
					if(b1 == b2 && c1 == c2 && b1 != c1) {
						done = true;
						break;
					}
				}
			}
			if(done) {
				fout.append("7\n");
				continue;
			}
			fout.append("-1\n");
		}
		System.out.print(fout);
	}
}
