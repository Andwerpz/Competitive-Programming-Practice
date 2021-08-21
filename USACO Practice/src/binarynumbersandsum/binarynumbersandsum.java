//package binarynumbersandsum;

import java.util.*;
import java.io.*;

public class binarynumbersandsum {
	public static void main(String[] args) throws IOException {
		
		//1066E
		
		//you just have to figure out for each bit in number b, how much does it contribute to the total answer. 
		
		//Since every time you divide b by 2, you also contribute to the answer, for every '1' bit in b, sum up all the bits that are greater than or equal to itself, and that is it's contribution.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long ans = 0;
		long mod = 998244353;
		long curSum = 0;
		long power = 1;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int pointer = n - 1;
		char[] a = fin.readLine().toCharArray();
		char[] b = fin.readLine().toCharArray();
		for(int i = b.length - 1; i >= 0; i--) {
			if(pointer >= 0 && a[pointer] == '1') {
				curSum += power;
				curSum %= mod;
			}
			if(b[i] == '1') {
				ans += curSum;
				ans %= mod;
			}
			power *= 2;
			power %= mod;
			pointer --;
		}
		System.out.println(ans);
	}
}
