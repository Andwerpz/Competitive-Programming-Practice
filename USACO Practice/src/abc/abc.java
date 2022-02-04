//package abc;

import java.util.*;
import java.io.*;

public class abc {
	public static void main(String[] args) throws IOException {
		
		//1632A
		
		//notice that any case with above 3 length is automatically bad. This is true since all 8 permutations of length 3
		//are bad, and every permutation of length > 3 includes a permutation of 3, so all those are also bad
		
		//out of the 4 length 2 permutations, only 10 and 01 are valid
		
		//all 2 length 1 permutations are valid
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			if(n >= 3) {
				fout.append("NO\n");
				continue;
			}
			if(n == 1) {
				fout.append("YES\n");
				continue;
			}
			fout.append(s[0] == s[1]? "NO\n" : "YES\n");
		}
		System.out.print(fout);
	}
}
