//package reverseandconcatenate;

import java.util.*;
import java.io.*;

public class reverseandconcatenate {
	public static void main(String[] args) throws IOException {
		
		//1634A
		
		//given string s, let us define 0 = s, and 1 = rev(s). 
		
		//notice that when given 1 operation, the possible outcomes are 01 and 10. 
		//on the second operation, the first one can generate 0110 and 1001, and the second one: 1001, 0110. Notice that they come up with the exact same answers. 
		
		//it is because when doing an operation, the two outcomes that you generate are exact opposites of each other, for example rev(0110) = 1001. 
		//so the answer in most cases is 2, except for when 0 == 1, in that case the answer is 1. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			boolean isPalindrome = true;
			for(int i = 0; i < n; i++) {
				if(s[i] != s[n - i - 1]) {
					isPalindrome = false;
					break;
				}
			}
			fout.append(isPalindrome || k == 0? "1\n" : "2\n");
		}
		System.out.print(fout);
	}
}
