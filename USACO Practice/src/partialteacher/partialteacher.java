//package partialteacher;

import java.util.*;
import java.io.*;

public class partialteacher {
	public static void main(String[] args) throws IOException {
		
		//67A
		
		//so... an 'L' means that the number on the left is bigger and a 'R' means that the right number is bigger. So if you have a bunch of 'L's on your right, that means that you are at least
		//that number, the number of 'L's. Take the max between that and the number of 'R's on the left. You count until you hit the other letter, because when you hit the other letter
		//you pretty much break the chain, saying that the number on the other side is greater, so you don't need to prop up the original number any more to satisfy the requirement
		//that everyone needs to be given at least 1 toffee. When hitting equals signs, you don't reset the count, but you don't stop it either. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int[] pfx = new int[n];
		int[] sfx = new int[n];
		for(int i = 0; i < n; i++) {
			if(i == 0) {
				pfx[i] = 1;
			}
			else {
				if(s[i - 1] == 'L') {
					pfx[i] = 1;
				}
				else if(s[i - 1] == '=') {
					pfx[i] = pfx[i - 1];
				}
				else {
					pfx[i] = pfx[i - 1] + 1;
				}
			}
		}
		for(int i = n - 1; i >= 0; i--) {
			if(i == n - 1) {
				sfx[i] = 1;
			}
			else {
				if(s[i] == 'R') {
					sfx[i] = 1;
				}
				else if(s[i] == '=') {
					sfx[i] = sfx[i + 1];
				}
				else {
					sfx[i] = sfx[i + 1] + 1;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			fout.append(Math.max(pfx[i], sfx[i])).append(" ");
		}
		System.out.println(fout);
	}
}
