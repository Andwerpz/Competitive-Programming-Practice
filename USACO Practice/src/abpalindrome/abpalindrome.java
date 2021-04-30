//package abpalindrome;

import java.util.*;
import java.io.*;

public class abpalindrome {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int num0 = Integer.parseInt(st.nextToken());
			int num1 = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int n = s.length;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '0') {
					if(s[n - 1 - i] == '?') {
						s[n - 1 - i] = '0';
					}
				}
				else if(s[i] == '1') {
					if(s[n - 1 - i] == '?') {
						s[n - 1 - i] = '1';
					}
				}
				//System.out.println(String.valueOf(s));
			}
			
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '0') {
					num0 --;
				}
				if(s[i] == '1') {
					num1 --;
				}
			}
			//System.out.println("preprocess: " + num0 + " " + num1);
			for(int i = 0; i <= s.length / 2; i++) {
				//System.out.println(i);
				if(s[i] == '?') {
					if(i == n - i - 1) {
						//System.out.println("middle value");
						if(num0 >= 1) {
							s[i] = '0';
							s[n - i - 1] = '0';
							num0 --;
						}
						else {
							s[i] = '1';
							s[n - i - 1] = '1';
							num1 --;
						}
					}
					else if(num0 >= 2) {
						s[i] = '0';
						s[n - i - 1] = '0';
						num0 -= 2;
					}
					else {
						s[i] = '1';
						s[n - i - 1] = '1';
						num1 -= 2;
					}
				}
			}
			boolean isValid = true;
			for(int i = 0; i < s.length; i++) {
				if(s[i] != s[n - i - 1]) {
					isValid = false;
				}
			}
			//System.out.println("final: " + String.valueOf(s));
			if(num0 == 0 && num1 == 0 && isValid) {
				fout.append(String.valueOf(s) + "\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
