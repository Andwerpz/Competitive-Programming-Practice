//package removethesubstringhardversion;

import java.util.*;
import java.io.*;

public class removethesubstringhardversion {
	public static void main(String[] args) throws IOException {
		
		//1203D2
		
		//first, assign each of the characters of subsequence t a position within subsequence s. For each character, it should be the most rightmost position that they can occupy. Then
		//starting from the leftmost character in t, move them to the leftmost position. Record for each the maximum space in between characters. Return the max.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		int n = s.length;
		int[] positions = new int[n];
		int pointer = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == t[pointer]) {
				positions[pointer] = i;
				pointer ++;
			}
			if(pointer == t.length) {
				break;
			}
		}
		int ans = n - positions[t.length - 1] - 1;
		pointer = t.length - 1;
		for(int i = n - 1; i >= 0; i --) {
			if(i < positions[pointer]) {
				break;
			}
			if(s[i] == t[pointer]) {
				positions[pointer] = i;
				if(pointer != 0) {
					ans = Math.max(ans, positions[pointer] - positions[pointer - 1] - 1);
				}
				else {
					ans = Math.max(ans, i);
				}
				pointer --;
			}
			if(pointer == -1) {
				break;
			}
		}
		System.out.println(ans);
	}
}
