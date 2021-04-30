//package stringgame;

import java.io.*;
import java.util.*;

public class stringgame {
	
	static char[] s;
	static char[] sNew;
	static int[] nums;
	
	public static boolean isValid(int j) {
		boolean[] removed = new boolean[s.length];
		for(int i = 0; i <= j; i++) {
			removed[nums[i]] = true;
			//System.out.print(nums[i] + " ");
		}
		System.out.println();
		int p = 0;
		for(int i = 0; i < s.length; i++) {
			char next = s[i];
			if(sNew[p] == next && !removed[i]) {
				p ++;
				if(p == sNew.length) {
					return true;
				}
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		s = fin.readLine().toCharArray();
		sNew = fin.readLine().toCharArray();
		nums = new int[s.length];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < nums.length; i++) {
			nums[i] = Integer.parseInt(st.nextToken()) - 1;
		}
		int low = 0;
		int high = s.length - 1;
		int mid = low + (high - low) / 2;
		int ans = low;
		while(low <= high) {
			if(isValid(mid)) {
				if(mid > ans) {
					ans = mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(mid);
	}
}
