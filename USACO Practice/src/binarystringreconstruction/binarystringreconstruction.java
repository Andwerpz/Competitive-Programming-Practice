//package binarystringreconstruction;

import java.util.*;
import java.io.*;

public class binarystringreconstruction {
	public static void main(String[] args) throws IOException {
		
		//1400C
		
		//notice that if there is a 0 in the result string at position i, you know that there must be a 0 at position i + x and i - x in the initial string. Just go through all the positions with 0 in the 
		//result string, and set the answer to 0s wherever needed. Then go through all the 1s, and check whether they are valid or not.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			char[] ans = new char[s.length];
			Arrays.fill(ans, '1');
			int x = Integer.parseInt(fin.readLine());
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '0') {
					if(i + x < s.length) {
						ans[i + x] = '0';
					}
					if(i - x >= 0) {
						ans[i - x] = '0';
					}
				}
			}
			boolean isValid = true;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '1') {
					if((i + x < s.length? ans[i + x] == '0' : true) && (i - x >= 0? ans[i - x] == '0' : true)) {
						isValid = false;
						break;
					}
				}
			}
			if(isValid) {
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
