package abpalindrome;

import java.util.*;
import java.io.*;

public class abpalindromever1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int num0 = Integer.parseInt(st.nextToken());
			int num1 = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			boolean isValid = true;
			int n = s.length;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '0') {
					if(s[n - 1 - i] == '?') {
						s[n - 1 - i] = '0';
					}
					num0 --;
				}
				else if(s[i] == '1') {
					if(s[n - 1 - i] == '?') {
						s[n - 1 - i] = '1';
					}
					num1 --;
				}
				else {
					if(s[n - 1 - i] == '0') {
						s[i] = '0';
						num0 --;
					}
					if(s[n - 1 - i] == '1') {
						s[i] = '1';
						num1 --;
					}
				}
				System.out.println(String.valueOf(s));
				System.out.println(num0 + " " + num1);
			}
			System.out.println(num0 + " " + num1);
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '?') {
					if(s[n - 1 - i] == '0') {
						s[i] = '0';
						num0 --;
					}
					else if(s[n - 1 - i] == '1') {
						s[i] = '1';
						num1 --;
					}
					else if(s[n - 1 - i] == '?') {
						if(n - 1 - i == i) {
							System.out.println("middle value");
							if(num1 >= 1) {	//nice
								s[i] = '1';
								num1 --;
							}
							else {
								s[i] = '0';
								num0 --;
							}
						}
						else if(num1 >= 2) {
							s[i] = '1';
							s[n - 1 - i] = '1';
							num1 -= 2;
						}
						else {
							s[i] = '0';
							s[n - 1 - i] = '0';
							num0 -= 2;
						}
					}
				}
				else if(s[i] == '0') {
					if(s[n - 1 - i] == '?') {
						s[n - 1 - i] = '0';
						num0 --;
					}
				}
				else {
					if(s[n - 1 - i] == '?') {
						s[n - 1 - i] = '1';
						num1 --;
					}
				}
				System.out.println(String.valueOf(s));
				System.out.println(num0 + " " + num1);
			}
			if(num0 < 0 || num1 < 0 || num1 != 0 || num0 != 0) {
				isValid = false;
			}
			for(int i = 0; i < n / 2; i++) {
				if(s[i] != s[n - 1 - i] || s[i] == '?' || s[n - 1 - i] == '?') {
					isValid = false;
					break;
				}
			}
			System.out.println(num0 + " " + num1);
			if(isValid) {
				fout.append(String.valueOf(s)).append("\n");
			}
			else {
				fout.append("-1\n");
			}
			
		}
		System.out.print(fout);
	}
}
