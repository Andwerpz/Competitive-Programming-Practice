//package backspace;

import java.util.*;
import java.io.*;

public class backspace {
	
	public static boolean isValid(char[] s, char[] q, int pointer) {
		boolean isValid = true;
		for(int i = 0; i < q.length; i++) {
			if(i == 0) {
				while(pointer < s.length && s[pointer] != q[i]) {
					pointer ++;
				}
				if(pointer == s.length) {
					isValid = false;
					break;
				}
			}
			else {
				pointer ++;
				if(pointer >= s.length) {
					isValid = false;
					break;
				}
				if(s[pointer] != q[i]) {
					while(pointer < s.length && s[pointer] != q[i]) {
						pointer += 2;
					}
					if(pointer >= s.length) {
						isValid = false;
						break;
					}
				}
			}
		}
		return isValid;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1553D
		
		//to solve, you need to go backwards. Start at the last possible valid position, it must be an even distance from the end.
		
		//make sure to catch edge cases always :((
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			char[] q = fin.readLine().toCharArray();
			boolean isValid = true;
			int pointer = s.length - 1;
//			for(int i = 0; i < Math.min(3, s.length); i++) {
//				isValid |= isValid(s, q, i);
//			}
			while(pointer >= 0 && s[pointer] != q[q.length - 1]) {
				pointer -= 2;
			}
			if(pointer < 0) {
				isValid = false;
			}
			for(int i = q.length - 2; i >= 0; i--) {
				//System.out.println(pointer);
				pointer --;
				if(pointer < 0) {
					isValid = false;
					break;
				}
				if(s[pointer] != q[i]) {
					while(pointer >= 0 && s[pointer] != q[i]) {
						pointer -= 2;
					}
					if(pointer < 0) {
						isValid = false;
						break;
					}
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
