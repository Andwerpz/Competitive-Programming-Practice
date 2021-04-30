//package diversegarland;

import java.util.*;
import java.io.*;

public class diversegarland {
	public static void main(String[] args) throws IOException{
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int ans = 0;
		for(int i = 1; i < n; i++) {
			if(s[i] == s[i - 1]) {
				ans ++;
				if(s[i - 1] == 'R') {
					if(i + 1 == n) {
						s[i] = 'G';
					}
					else if(s[i + 1] == 'R') {
						s[i] = 'G';
					}
					else if(s[i + 1] == 'G') {
						s[i] = 'B';
					}
					else if(s[i + 1] == 'B') {
						s[i] = 'G';
					}
				}
				else if(s[i - 1] == 'G') {
					if(i + 1 == n) {
						s[i] = 'B';
					}
					else if(s[i + 1] == 'R') {
						s[i] = 'B';
					}
					else if(s[i + 1] == 'G') {
						s[i] = 'B';
					}
					else if(s[i + 1] == 'B') {
						s[i] = 'R';
					}
				}
				else if(s[i - 1] == 'B') {
					if(i + 1 == n) {
						s[i] = 'R';
					}
					else if(s[i + 1] == 'R') {
						s[i] = 'G';
					}
					else if(s[i + 1] == 'G') {
						s[i] = 'R';
					}
					else if(s[i + 1] == 'B') {
						s[i] = 'G';
					}
				}
			}
		}
		System.out.println(ans + "\n" + String.valueOf(s));
	}
}
