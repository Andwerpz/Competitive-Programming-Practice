//package specialtask;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class specialtask {
	public static void main(String[] args) throws IOException {
		
		//316A2
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		BigInteger num = new BigInteger("1");
		StringBuilder zeroes = new StringBuilder();
		HashSet<Character> dict = new HashSet<Character>();
		for(int i = 0; i < s.length; i++) {
			if(Character.isAlphabetic(s[i])) {
				if(i == 0) {
					num = num.multiply(new BigInteger("9"));
					dict.add(s[i]);
				}
				else {
					if(!dict.contains(s[i])) {
						num = num.multiply(new BigInteger((10 - dict.size()) + ""));
						dict.add(s[i]);
					}
				}
			}
			else if(s[i] == '?') {
				if(i == 0) {
					num = num.multiply(new BigInteger("9"));
				}
				else {
					zeroes.append("0");
				}
			}
		}
		System.out.println(num + "" + zeroes);
	}
}
