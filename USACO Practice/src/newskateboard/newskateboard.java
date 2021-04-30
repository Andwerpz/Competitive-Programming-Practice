//package newskateboard;

import java.util.*;
import java.io.*;

public class newskateboard {
	public static void main(String[] args) throws IOException {
		
		//im dumb lol. The number is divisible by 4 if the first two numbers are divisible by 4. 
		//iterate through the digit array, checking the current number and the next number to see if they are divisible.
		//if they are, then add the amount of numbers remaining in the array
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] sTemp = fin.readLine().toCharArray();
		int n = sTemp.length;
		int[] s = new int[n];
		long ans = 0;
		for(int i = 0; i < n; i++) {
			s[i] = Integer.parseInt(sTemp[i] + "");
			if(s[i] % 4 == 0) {
				ans++;
			}
		}
		for(int i = n - 1; i >= 1; i--) {
			int val = s[i] + (s[i - 1] * 10);
			if(val % 4 == 0) {
				ans += i;
			}
		}
		System.out.println(ans);
	}
}
