//package reversestring;

import java.util.*;
import java.io.*;

public class reversestring {
	
	public static boolean isValid(char[] s, char[] q, int pointer) {
		boolean isValid = false;
		for(int i = 1; i < q.length; i++) {
			if(pointer - 1 >= 0 && s[pointer - 1] == q[i]) {
				isValid |= moveLeft(s, q, pointer - 1, i + 1);
			}
			if(pointer + 1 < s.length && s[pointer + 1] == q[i]) {
				pointer ++;
				if(i == q.length - 1) {
					isValid = true;
				}
			}
			else {
				break;
			}
		}
		if(q.length == 1) {
			isValid = true;
		}
		return isValid;
	}
	
	public static boolean moveLeft(char[] s, char[] q, int pointer, int sPointer) {
		for(int i = sPointer; i < q.length; i++) {
			if(pointer - 1 >= 0 && s[pointer - 1] == q[i]) {
				pointer --;
			}
			else {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1553B
		
		//since the input is so small, we can take a O(n^2) approach. iterate through s and locate all positions that are equal to the starting letter of q. Test each position, moving as far
		//as you can to the right. Whenever you can move to the left, test it, by moving as far as you can to the left. If one location is valid, then the input is valid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			char[] q = fin.readLine().toCharArray();
			boolean isValid = false;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == q[0] && isValid(s, q, i)) {
					isValid = true;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
