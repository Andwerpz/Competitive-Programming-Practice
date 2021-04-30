//package tmtdocument;

import java.util.*;
import java.io.*;

public class tmtdocument {
	public static void main(String[] args) throws IOException {
		
		//for each 'M' in the string, start from left to right and assign it a 'T'. Do the same but the next time going from left to right. 
		//if at any time, the 'T' being assigned to the 'M' doesn't follow the TMT format, then this string is invalid.
		
		//the string must start with 1/3 'M's and 2/3 'T's
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			boolean[] v = new boolean[n];
			int mCount = 0;
			int[] m = new int[n / 3];
			for(int i = 0; i < n; i++) {
				if(s[i] == 'M') {
					m[mCount % (n / 3)] = i;
					mCount ++;
				}
			}
			if(mCount != n / 3) {
				fout.append("NO\n");
			}
			else {
				boolean isValid = true;
				int count = 0;
				int pointer = 0;
				for(int i = 0; i < n; i++) {
					if(s[i] == 'T') {
						if(i > m[count]) {
							isValid = false;
							break;
						}
						count ++;
						if(count == n / 3) {
							break;
						}
					}
				}
				count = mCount - 1;
				for(int i = n - 1; i >= 0; i--) {
					if(s[i] == 'T') {
						if(i < m[count]) {
							isValid = false;
							break;
						}
						count --;
						if(count == -1) {
							break;
						}
					}
				}
				if(isValid) {
					fout.append("YES\n");
				}
				else {
					fout.append("NO\n");
				}
			}
		}
		System.out.print(fout);
	}
}
