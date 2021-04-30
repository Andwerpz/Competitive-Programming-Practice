//package moneysums;

import java.util.*;
import java.io.*;

public class moneysums {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		int[] coins = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			coins[i] = Integer.parseInt(st.nextToken());
		}
		TreeSet<Integer> s = new TreeSet<Integer>();
		for(int i = 0; i < coins.length; i++) {
			TreeSet<Integer> next = new TreeSet<Integer>();
			for(int c : s) {
				if(!s.contains(c + coins[i])) {
					next.add(c + coins[i]);
				}
				
			}
			if(!s.contains(coins[i])) {
				next.add(coins[i]);
			}
			s.addAll(next);
		}
		for(int i : s) {
			fout.append(i).append(" ");
		}
		System.out.println(s.size() + "\n" + fout.substring(0, fout.length() - 1));
	}
}
