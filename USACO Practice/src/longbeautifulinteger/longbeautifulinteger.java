//package longbeautifulinteger;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class longbeautifulinteger {
	public static void main(String[] args) throws IOException {
		
		//1268A
		
		//go down the line and match digits, starting from the greatest digit. If you see a digit that is lower than the one you are matching it with, then
		//you can just repeat the first k digits. If you haven't found a lower digit, and you encounter a higher digit, then you need to repeat the first k digits,
		//but add 1 to the value.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		char[] repeat = String.valueOf(s).substring(0, k).toCharArray();
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			if(s[i] < repeat[i % k]) {
				break;
			}
			if(s[i] > repeat[i % k]) {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			char[] ans = new char[n];
			for(int i = 0; i < n; i++) {
				ans[i] = repeat[i % k];
			}
			System.out.println(ans.length);
			System.out.println(ans);
		}
		else {
			boolean needLarge = true;
			for(int i = 0; i < k; i++) {
				if(repeat[i] != '9') {
					needLarge = false;
				}
			}
			char[] ans = new char[needLarge? n + 1 : n];
			if(needLarge) {
				repeat = new char[k + 1];
				repeat[0] = '1';
				for(int i = 1; i < repeat.length; i++) {
					repeat[i] = '0';
				}
			}
			else {
				repeat[k - 1] ++;
				for(int i = repeat.length - 1; i >= 0 && repeat[i] == ':'; i--) {
					repeat[i] = '0';
					repeat[i - 1] ++;
				}
			}
			for(int i = 0; i < ans.length; i++) {
				ans[i] = repeat[i % repeat.length];
			}
			System.out.println(ans.length);
			System.out.println(ans);
		}
	}
}
