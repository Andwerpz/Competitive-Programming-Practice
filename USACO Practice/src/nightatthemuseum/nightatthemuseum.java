//package nightatthemuseum;

import java.util.*;
import java.io.*;

public class nightatthemuseum {
	public static void main(String[] args) throws IOException {
		
		//731A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] c = new char[26];
		for(char i = 'a'; i <= 'z'; i++) {
			c[i - 'a'] = i;
		}
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		
		int base = 26 * 100000;
		int pointer = base;
		int dist = 0;
		for(int i = 0; i < n; i++) {
			int clockwise = pointer;
			int counterclockwise = pointer;
			
			while(c[clockwise % 26] != s[i]) {
				clockwise ++;
			}
			while(c[counterclockwise % 26] != s[i]) {
				counterclockwise --;
			}
			//System.out.println(Math.min(clockwise - pointer, pointer - counterclockwise));
			dist += Math.min(clockwise - pointer, pointer - counterclockwise);
			pointer = s[i] - 'a' + base;
			//System.out.println(c[pointer % 26]);
		}
		System.out.println(dist);
	}
}
