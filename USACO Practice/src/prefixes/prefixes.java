//package prefixes;

import java.util.*;
import java.io.*;

public class prefixes {
	public static void main(String[] args) throws IOException {
		
		//1216A
		
		//all groups of 2 letters are independent. 
		
		//just check if each group of letters are the same. If they are the same, then you need to do an operation
		//to make one of them different.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int ans = 0;
		char[] s = fin.readLine().toCharArray();
		for(int i = 0; i < n; i += 2) {
			if(s[i] == s[i + 1]) {
				ans ++;
				s[i] = s[i] == 'a'? 'b' : 'a';
			}
		}
		System.out.println(ans + "\n" + String.valueOf(s));
	}
}
