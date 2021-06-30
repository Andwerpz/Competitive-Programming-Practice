//package crackingthecode;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class crackingthecode {
	public static void main(String[] args) throws IOException {
		
		//630L
		
		//just implement the problem statement
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		char temp = s[1];
		s[1] = s[4];
		s[4] = temp;
		temp = s[2];
		s[2] = s[1];
		s[1] = temp;
		BigInteger num = new BigInteger(String.valueOf(s));
		num = num.pow(5);
		num = num.mod(new BigInteger("100000"));
		String ans = num.toString();
		while(ans.length() != 5) {
			ans = "0" + ans;
		}
		System.out.println(ans);
	}
}
