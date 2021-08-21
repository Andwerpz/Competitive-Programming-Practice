//package cuttingout;

import java.util.*;
import java.io.*;

public class cuttingout {
	
	public static boolean isValid(ArrayList<int[]> amt, int val, int k) {
		if(val == 0) {
			return true;
		}
		int counter = 0;
		for(int i = 0; i < amt.size(); i++) {
			counter += amt.get(i)[0] / val;
		}
		return counter >= k;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1077D
		
		//just binary search to find the maximum amount of duplicate arrays you can make.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			dict.put(next, dict.getOrDefault(next, 0) + 1);
		}
		ArrayList<int[]> amt = new ArrayList<int[]>();
		for(int i : dict.keySet()) {
			amt.add(new int[] {dict.get(i), i});
		}
		amt.sort((a, b) -> -(a[0] - b[0]));
		int high = n;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = low;
		while(low <= high) {
			if(isValid(amt, mid, k)) {
				ans = Math.max(ans, mid);
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		if(ans == 0) {
			
		}
		else {
			int counter = 0;
			StringBuilder fout = new StringBuilder();
			outer:
			for(int i = 0; i < amt.size(); i++) {
				while(amt.get(i)[0] >= ans) {
					fout.append(amt.get(i)[1]).append(" ");
					amt.get(i)[0] -= ans;
					counter ++;
					if(counter == k) {
						break outer;
					}
				}
			}
			System.out.println(fout);
		}
		
		//System.out.println(ans);
		
	}
}
