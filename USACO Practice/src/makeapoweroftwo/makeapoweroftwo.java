//package makeapoweroftwo;

import java.util.*;
import java.io.*;

public class makeapoweroftwo {
	public static void main(String[] args) throws IOException {
		
		//1560D
		
		//precompute all possible powers of 2 with less than or equal to 9 digits. From there, just get the minimum amount of moves required to transform the number into one of the powers of two.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		char[][] power = new char[60][];
		long pointer = 1;
		for(int i = 0; i < power.length; i++) {
			String next = pointer + "";
			power[i] = next.toCharArray();
			pointer *= 2;
		}
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = (n + "").toCharArray();
			int ans = Integer.MAX_VALUE;
			for(int i = 0; i < power.length; i++) {
				int numOperations = 0;
				pointer = 0;
				for(int j = 0; j < power[i].length; j++) {
					while(pointer != s.length && s[(int) pointer] != power[i][j]) {
						pointer ++;
						numOperations ++;
					}
					if(pointer == s.length) {
						numOperations ++;
					}
					else {
						pointer ++;
					}
				}
				numOperations += s.length - pointer;
				//System.out.println(String.valueOf(power[i]) + " " + numOperations);
				ans = Math.min(ans, numOperations);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
