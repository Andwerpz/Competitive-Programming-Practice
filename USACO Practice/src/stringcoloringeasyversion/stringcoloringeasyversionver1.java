package stringcoloringeasyversion;

import java.util.*;
import java.io.*;

public class stringcoloringeasyversionver1 {
	public static void main(String[] args) throws IOException {
		
		//maybe try finding out if the sequence can be represented by two non-decreasing subsequences. yes yes yes
		//since you can only switch numbers of the same color, the sequence in each non-decreasing subsequence won't change, but you can jostle around 
		//with the numbers in the other subsequence, giving you the ability to sort the subsequence.
		
		//can't greedily choose the longest increasing subsequence.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = s[i];
		}
		ArrayList<HashSet<Integer>> order = new ArrayList<HashSet<Integer>>();
		for(int i = 0; i < n + 1; i++) {
			order.add(new HashSet<Integer>());
		}
		order.get(0).add(nums[0]);
		int[] dp = new int[n + 1];
		Arrays.fill(dp, Integer.MAX_VALUE);
		dp[0] = 0;
		int max = 0;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			int pointer = 0;
			while(next >= dp[pointer]) {
				pointer ++;
			}
			HashSet<Integer> nextSet = new HashSet<Integer>();
			nextSet.addAll(order.get(pointer - 1));
			nextSet.add(i);
			order.set(pointer, nextSet);
			dp[pointer] = next;
			max = Math.max(max, pointer);
		}
		for(int i : dp) {
			System.out.print(i + " ");
		}
		System.out.println();
		int prev = -1;
		boolean isValid = true;
		StringBuilder fout = new StringBuilder();
		HashSet<Integer> check = order.get(max);
		for(int i = 0; i < n; i++) {
			if(!check.contains(i)) {
				int next = nums[i];
				System.out.println(next + " " + i);
				if(next >= prev || prev == -1) {
					prev = next;
					fout.append("0");
				}
				else {
					isValid = false;
					break;
				}
			}
			else {
				fout.append("1");
			}
		}
		if(isValid) {
			System.out.println("YES\n" + fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
