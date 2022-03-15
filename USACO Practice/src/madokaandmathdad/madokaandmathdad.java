//package madokaandmathdad;

import java.util.*;
import java.io.*;

public class madokaandmathdad {
	public static void main(String[] args) throws IOException {
		
		//1647A
		
		//notice that in order to get the largest number, you first want to optimize the amount of
		//digits it has.
		
		//if you could just have n digits, each being '1', then it would make the largest number, but
		//according to the rules, you can't have two consecutive digits be the same.
		
		//what if you used the second smallest number: 2, and alternated between them?
		
		//notice that using only 1 and 2, you can construct any n,
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int cur = n % 3 == 1? 1 : 2;
			while(n != 0) {
				n -= cur;
				fout.append(cur);
				cur = cur == 1? 2 : 1;
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
