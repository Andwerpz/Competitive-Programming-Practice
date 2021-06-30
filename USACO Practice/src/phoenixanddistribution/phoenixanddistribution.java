//package phoenixanddistribution;

import java.util.*;
import java.io.*;

public class phoenixanddistribution {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] chars = new int[26];
			String base = "";
			char[] s = fin.readLine().toCharArray();
			for(int i = 0; i < n; i++) {
				chars[s[i] - 'a'] ++;
			}
			char pointer = 'a';
			//System.out.println(String.valueOf(s));
			while(n > 0) {
				//System.out.println(n);
				while(pointer < (char) ('z' + 1) && chars[pointer - 'a'] == 0) {
					pointer ++;
				}
				if(pointer == (char) ('z' + 1)) {
					break;
				}
				if(chars[pointer - 'a'] >= k) {
					chars[pointer - 'a'] -= k;
					n -= k;
					base += pointer;
				}
				else if(chars[pointer - 'a'] < k) {
					int charsLeft = k;
					char max = pointer;
					for(int i = 0; i < 26; i++) {
						if(chars[i] != 0) {
							if(chars[i] >= charsLeft) {
								max = (char) ('a' + i);
								break;
							}
							else {
								charsLeft -= chars[i];
								chars[i] = 0;
							}
						}
					}
					base += max;
					break;
				}
			}
			fout.append(base).append("\n");
		}
		System.out.print(fout);
	}
}
