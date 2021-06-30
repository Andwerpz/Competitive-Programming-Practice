//package servalandparenthesissequence;

import java.util.*;
import java.io.*;

public class servalandparenthesissequence {
	public static void main(String[] args) throws IOException {
		
		//1153C
		
		//just make the first n / 2 question marks into right facing parenthesis: '(', and the last n / 2 ones into left facing parenthesis: ')'
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int left = 0;
		int right = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == '(') {
				left ++;
			}
			else if(s[i] == ')') {
				right ++;
			}
		}
		for(int i = 0; i < n; i++) {
			if(left == n / 2) {
				break;
			}
			else if(s[i] == '?') {
				s[i] = '(';
				left ++;
			}
		}
		for(int i = 0; i < n; i++) {
			if(right == n / 2) {
				break;
			}
			else if(s[i] == '?') {
				s[i] = ')';
				right ++;
			}
		}
		boolean isValid = true;
		if(s.length % 2 == 1) {
			isValid = false;
		}
		else if(left > n / 2 || right > n / 2) {
			isValid = false;
		}
		for(int i = 0; i < n - 1; i++) {
			if(s[i] == '(') {
				left ++;
			}
			else if(s[i] == ')') {
				right ++;
			}
			if(left == right || right > left) {
				isValid = false;
				break;
			}
		}
		System.out.println(isValid? String.valueOf(s) : ":(");
	}
}
