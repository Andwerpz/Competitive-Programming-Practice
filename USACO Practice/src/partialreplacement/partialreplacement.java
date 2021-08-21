//package partialreplacement;

import java.util.*;
import java.io.*;

public class partialreplacement {
	public static void main(String[] args) throws IOException {
		
		//1506B
		
		//starting from the first 'x', just place each subsequent 'x' as far as you can.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int start = 0;
			int pointer = 0;
			int ans = 1;
			while(s[start] != '*') {
				start ++;
			}
			while(true) {
				pointer = start + k;
				//System.out.println(pointer);
				while(pointer >= s.length || s[pointer] != '*') {
					if(pointer == start) {
						break;
					}
					pointer --;
				}
				if(pointer == start) {
					break;
				}
				start = pointer;
				ans ++;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
