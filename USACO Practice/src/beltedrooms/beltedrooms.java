//package beltedrooms;

import java.util.*;
import java.io.*;

public class beltedrooms {
	public static void main(String[] args) throws IOException {
		
		//1428B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			boolean allOne = true;
			char prev = 0;
			for(int i = 0; i < n; i++) {
				if(s[i] != '-') {
					if(prev == 0) {
						prev = s[i];
					}
					else if(prev != s[i]) {
						allOne = false;
						break;
					}
				}
			}
			if(allOne) {
				fout.append(n).append("\n");
			}
			else {
				int ans = 0;
				for(int i = n; i < n * 2; i++) {
					if(s[(i - 1) % n] == '-' || s[i % n] == '-') {
						ans ++;
					}
				}
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
