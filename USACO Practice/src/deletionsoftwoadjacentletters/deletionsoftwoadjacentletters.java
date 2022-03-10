//package deletionsoftwoadjacentletters;

import java.util.*;
import java.io.*;

public class deletionsoftwoadjacentletters {
	public static void main(String[] args) throws IOException {
		
		//1650A
		
		//just check if there exists the char c on an even numbered index
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			char c = fin.readLine().charAt(0);
			boolean isValid = false;
			for(int i = 0; i < s.length; i += 2) {
				if(s[i] == c) {
					isValid = true;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
