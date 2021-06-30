//package goodstring;

import java.util.*;
import java.io.*;

public class goodstring {
	public static void main(String[] args) throws IOException {
		
		//1389C
		
		//since the remaining string has to be even with two repeating digits, you can just brute force all the combinations until you find the longest one.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int ans = s.length;
			int n = s.length;
			for(int i = 0; i < 10; i++) {
				for(int j = 0; j < 10; j++) {
					int cur = s.length;
					char a = (i + "").charAt(0);
					char b = (j + "").charAt(0);
					if(a == b) {
						for(int k = 0; k < n; k++) {
							if(s[k] == a) {
								cur --;
							}
						}
					}
					else {
						boolean which = true;
						for(int k = 0; k < n; k++) {
							if(which && s[k] == a) {
								which = false;
							}
							else if(!which && s[k] == b) {
								which = true;
								cur -= 2;
							}
							//System.out.println(which);
						}
					}
					//System.out.println(a + " " + b + " " + cur);
					ans = Math.min(ans, cur);
				}
			}
			System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
