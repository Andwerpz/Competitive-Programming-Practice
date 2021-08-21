//package binarydecimal;

import java.util.*;
import java.io.*;

public class binarydecimal {
	public static void main(String[] args) throws IOException {
		
		//1530A
		
		//just find the largest digit. That is the minimum number of operations required.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int ans = 0;
			for(int i = 0; i < s.length; i++) {
				ans = Math.max(ans, s[i] - '0');
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
