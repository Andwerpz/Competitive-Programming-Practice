//package roofconstruction;

import java.util.*;
import java.io.*;

public class roofconstruction {
	public static void main(String[] args) throws IOException {
		
		//1632B
		
		//if n is a power of 2, then in order to minimize, we just need to make every adjacent number differ in only 1 bit.
		
		//if n is not a power of 2, we can just start the bit sequence at n - 1, and get all the highest numbers first
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			HashSet<Integer> v = new HashSet<Integer>();
			int pointer = n - 1;
			for(int i = 0; i < n; i++) {
				v.add(pointer);
				fout.append(pointer).append(" ");
				char[] s = Integer.toBinaryString(pointer).toCharArray();
				int counter = s.length - 1;
				for(int j = 1; j <= n; j *= 2) {
					if((counter < 0 || s[counter] == '0') && pointer + j < n && !v.contains(pointer + j)) {
						pointer += j;
						break;
					}
					else if(counter >= 0 && s[counter] == '1' && pointer >= j && !v.contains(pointer - j)) {
						pointer -= j;
						break;
					}
					counter --;
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
