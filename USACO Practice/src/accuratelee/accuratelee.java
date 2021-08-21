//package accuratelee;

import java.util.*;
import java.io.*;

public class accuratelee {
	public static void main(String[] args) throws IOException {
		
		//1369B
		
		//all strings are going to end up in this format: a zeroes, b ones. 
		
		//if the string starts in the output format, then return the input.
		
		//else, take the leading zeros, add one more 0 and take the trailing ones. Concatenate them, and return.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			int numOnes = 0;
			int numZero = 0;
			for(int i = n - 1; i >= 0; i--) {
				if(s[i] == '1') {
					numOnes ++;
				}
				else {
					break;
				}
			}
			boolean touch = false;
			for(int i = 0; i < n; i++) {
				if(s[i] == '0') {
					numZero ++;
					if(i == n - numOnes - 1) {
						touch = true;
					}
				}
				else {
					break;
				}
			}
			if(numOnes != n) {
				if(!touch) {
					fout.append("0");
				}
				for(int i = 0; i < numZero; i++) {
					fout.append("0");
				}
			}
			for(int i = 0; i < numOnes; i++) {
				fout.append("1");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
