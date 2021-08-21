//package banhmi;

import java.util.*;
import java.io.*;

public class banhmi {
	public static void main(String[] args) throws IOException {
		
		//1062C
		
		//for this problem, you always want to eat the parts that were originally 1 first, then eat the 0s. This is so that for each turn, you increase the value of the other pieces
		//the most, resulting in the highest amount of tastieness. 
		
		//One thing that you have to keep in mind is that if you eat a piece that was originally 0, but is now greater than 0, it still adds to the values of all other pieces.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		long mod = (long) (1e9 + 7);
		char[] s = fin.readLine().toCharArray();
		int[] pfx = new int[n];
		for(int i = 0; i < n; i++) {
			if(s[i] == '1') {
				pfx[i] ++;
			}
			if(i != 0) {
				pfx[i] += pfx[i - 1];
			}
		}
		long[] power = new long[n];
		power[0] = 1;
		for(int i = 1; i < n; i++) {
			power[i] = power[i - 1] * 2;
			power[i] %= mod;
		}
		for(int i = 1; i < n; i++) {
			power[i] += power[i - 1];
			power[i] %= mod;
		}
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			int range = r - l + 1;
			int numOnes = pfx[r] - (l == 0? 0 : pfx[l - 1]);
			int numZero = range - numOnes; 
			long ans = 0;
			if(numOnes != 0) {
				//System.out.println(numZero + " " + power[numOnes - 1]);
				ans = power[numOnes - 1] + (numZero != 0? (power[numOnes - 1] * power[numZero - 1]) % mod: 0);
				ans %= mod;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
