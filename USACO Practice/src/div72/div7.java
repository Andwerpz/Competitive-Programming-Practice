//package div72;

import java.util.*;
import java.io.*;

public class div7 {
	public static void main(String[] args) throws IOException {
		
		//1633A
		
		//the inputs are small enough that you can brute force try all multiples of 7 from 1 - 1000
		//for each number and pick the one that changes the minimum amount of digits
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int minChange = 10;
			int ans = -1;
			String ns = n + "";
			int length = (n + "").length();
			for(int i = 0; i < 1000; i += 7) {
				String s = i + "";
				if(s.length() == length && i % 7 == 0) {
					int curChange = 0;
					for(int j = 0; j < length; j++) {
						if(ns.charAt(j) != s.charAt(j)) {
							curChange ++;
						}
					}
					if(curChange < minChange) {
						minChange = curChange;
						ans = i;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
