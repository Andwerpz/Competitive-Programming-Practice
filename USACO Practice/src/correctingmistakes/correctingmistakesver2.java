package correctingmistakes;

import java.util.*;
import java.io.*;

public class correctingmistakesver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		int start = 0;
		int end = n - 1;
		for(int i = 0; i < n; i++) {
			if(s[i] == t[i]) {
				start ++;
			}
			else {
				break;
			}
		}
		for(int i = n - 1; i >= 0; i--) {
			if(s[i] == t[i]) {
				end -- ;
			}
			else {
				break;
			}
		}
		boolean right = true;
		boolean left = true;
		for(int i = start; i < end; i++) {
			if(s[i] != t[i + 1]) {
				right = false;
			}
		}
		for(int i = start + 1; i <= end; i++) {
			if(s[i] != t[i - 1]) {
				left = false;
			}
		}
		if(start == end) {
			System.out.println(2);
		}
		else if(right || left){
			System.out.println(1);
		}
		else {
			System.out.println(0);
		}
	}
}
