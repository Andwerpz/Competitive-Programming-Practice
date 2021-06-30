//package makeapermutation;

import java.util.*;
import java.io.*;

public class makeapermutation {
	public static void main(String[] args) throws IOException {
		
		//you are given a set of n numbers, from 1 - n. You can perform q actions on the array, each action you change one number to whatever number you like. The goal of the problem
		//is to make the list of numbers into a permutation from 1 - n using the minimum possible moves, while minimizing its lexographic value. Minimum moves is the top priority, while lexographic
		//value is second. Since all numbers are from 1 - n, in order to make a permutation, all you have to do is eliminate all the duplicate values. And to simultaneously get the 
		//minimum possible permutation, you just put the smaller values at the front. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		TreeSet<Integer> missing = new TreeSet<Integer>();
		for(int i = 1; i <= n; i++) {
			missing.add(i);
		}
		for(int i = 0; i < n; i++) {
			if(missing.contains(nums[i])) {
				missing.remove(nums[i]);
			}
		}
		//System.out.println(missing);
		HashSet<Integer> dupeTest = new HashSet<Integer>();
		HashMap<Integer, Integer> duplicates = new HashMap<Integer, Integer>();
		boolean[] v = new boolean[n + 1];
		int ans = 0;
		for(int i = 0; i < n; i++) {
			if(dupeTest.contains(nums[i])) {
				ans ++;
				duplicates.put(nums[i], duplicates.getOrDefault(nums[i], 1) + 1);
			}
			dupeTest.add(nums[i]);
		}
		StringBuilder fout = new StringBuilder();
		fout.append(ans).append("\n");
		int pointer = 1;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			if(duplicates.containsKey(next)) {
				int nextMissing = next;
				if(missing.size() != 0) {
					nextMissing = missing.first();
				}
				if(!v[next]) {
					if(duplicates.get(next) == 1) {
						fout.append(next).append(" ");
						v[next] = true;
					}
					else if(nextMissing > next) {
						fout.append(next).append(" ");
						v[next] = true;
					}
					else {
						fout.append(nextMissing).append(" ");
						missing.pollFirst();
					}
				}
				else {
					fout.append(nextMissing).append(" ");
					missing.pollFirst();
				}
				duplicates.put(next, duplicates.get(next) - 1);
			}
			else {
				fout.append(next).append(" ");
				v[next] = true;
			}
		}
		System.out.println(fout);
	}
}
