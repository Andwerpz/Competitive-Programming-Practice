//package mikeandstrings;

import java.util.*;
import java.io.*;

public class mikeandstrings {
	
	public static int makeEqual(char[] a, char[] b) {	//return the amount of actions required to change b to equal a, if they can't be made equal, returns -1
		String aStr = (String) String.valueOf(a);
		String bStr = (String) String.valueOf(b);
		if(aStr.equals(bStr)) {
			return 0;
		}
		int ans = 1;
		for(int i = 0; i < b.length; i++) {
			bStr = bStr.substring(1, bStr.length()) + bStr.charAt(0);
			if(aStr.equals(bStr)) {
				return ans;
			}
			ans ++;
		}
		return -1;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] dp = new int[n];	//dp[i], the min number of moves considering the first i strings
		int min = Integer.MAX_VALUE;
		char[][] strings = new char[n][];
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			strings[i] = fin.readLine().toCharArray();
		}
		for(int i = 0; i < n; i++) {
			int sum = 0;
			for(int j = 0; j < n; j++) {
				int next = makeEqual(strings[i], strings[j]);
				if(next == -1) {
					isValid = false;
					break;
				}
				sum += next;
			}
			if(!isValid) {
				break;
			}
			if(min > sum) {
				min = sum;
			}
		}
		if(isValid) {
			System.out.println(min);
		}
		else {
			System.out.println(-1);
		}
	}
}
