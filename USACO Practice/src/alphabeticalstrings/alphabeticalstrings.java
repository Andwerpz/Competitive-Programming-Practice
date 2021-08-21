//package alphabeticalstrings;

import java.util.*;
import java.io.*;

public class alphabeticalstrings {
	public static void main(String[] args) throws IOException {
		
		//1547B
		
		//first, find where 'a' is, and then look to the left and right. As long as there is a valid letter to the left or right, then you can take that letter, 
		//and keep going. Else, the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			char next = 'a';
			int pointer = -1;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == next) {
					//System.out.println(i + " " + s[i]);
					pointer = i;
					next ++;
					break;
				}
			}
			boolean isValid = true;
			if(pointer == -1) {
				isValid = false;
			}
			int l = pointer - 1;
			int r = pointer + 1;
			while(r < s.length || l >= 0) {
				//System.out.println(l + " " + r);
				if(r < s.length && s[r] == next) {
					next ++;
					r ++;
				}
				else if(l >= 0 && s[l] == next) {
					next ++;
					l --;
				}
				else {
					isValid = false;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
