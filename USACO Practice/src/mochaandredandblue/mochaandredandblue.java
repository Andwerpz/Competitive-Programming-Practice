//package mochaandredandblue;

import java.util.*;
import java.io.*;

public class mochaandredandblue {
	public static void main(String[] args) throws IOException {
		
		//1559B
		
		//just greedily color alternating Rs and Bs. Whenever you hit a R or B that is not in line with your current pattern, just offset your pattern 1 color and keep going.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			char firstChar = 'R';
			char curChar = 'R';
			boolean isValid = true;
			int pointer = 0;
			while(pointer != n && s[pointer] == '?') {
				pointer ++;
				curChar = curChar == 'R'? 'B' : 'R';
			}
			if(pointer != n && s[pointer] != curChar) {
				firstChar = 'B';
			}
			curChar = firstChar;
			char[] ans = new char[n];
			for(int i = 0; i < n; i++) {
				if(s[i] != '?') {
					curChar = s[i];
				}
				ans[i] = curChar;
				curChar = curChar == 'R'? 'B' : 'R';
			}
			fout.append(String.valueOf(ans)).append("\n");
		}
		System.out.print(fout);
	}
}
