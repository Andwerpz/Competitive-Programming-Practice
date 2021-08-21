//package strangebirthdayparty;

import java.util.*;
import java.io.*;

public class strangebirthdayparty {
	public static void main(String[] args) throws IOException {
		
		//1471C
		
		//Our base case will be where you give everyone money. This is clearly the most expensive option. In order to decrease the money spent, you can start by giving the
		//most expensive person the cheapest gift, and continue on from there until you can't give any more gifts. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			Integer[] friends = new Integer[n];
			int[] prices = new int[m];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				friends[i] = Integer.parseInt(st.nextToken()) - 1;
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				prices[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(friends, Collections.reverseOrder());
			long sum = 0;
			int pointer = 0;
			for(int i = 0; i < friends.length; i++) {
				if(pointer <= friends[i]) {
					sum += prices[pointer];
					pointer ++;
				}
				else {
					sum += prices[friends[i]];
				}
			}
			fout.append(sum).append("\n");
		}
		System.out.print(fout);
	}
}
