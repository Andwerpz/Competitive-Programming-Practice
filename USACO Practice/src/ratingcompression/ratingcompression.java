//package ratingcompression;

import java.util.*;
import java.io.*;

public class ratingcompression {
	
	public static boolean isValid(int[] nums, int val) {
		Stack<Integer> s1 = new Stack<Integer>();
		Stack<Integer> s2 = new Stack<Integer>();
		Integer[] permutation = new Integer[nums.length - val + 1];
		int pointer = nums[0];
		for(int i = 0; i < val; i++) {
			pointer = Math.min(pointer, nums[i]);
			s1.push(nums[i]);
		}
		permutation[0] = pointer;
		for(int i = 1; i < permutation.length; i++) {
			if(s2.size() == 0) {
				pointer = s1.peek();
				while(s1.size() != 0) {
					pointer = Math.min(pointer, s1.pop());
					s2.push(pointer);
				}
				pointer = nums[i + val - 1];
			}
			s2.pop();
			pointer = Math.min(pointer, nums[i + val - 1]);
			s1.push(nums[i + val - 1]);
			if(s2.size() == 0) {
				permutation[i] = pointer;
			}
			else {
				permutation[i] = Math.min(pointer, s2.peek());
			}
		}
		boolean[] v = new boolean[permutation.length];
		for(int i = 0; i < permutation.length; i++) {
			int next = permutation[i] - 1;
			if(next > permutation.length - 1 || v[next]) {
				return false;
			}
			v[next] = true;
		}
		for(int i = 0; i < v.length; i++) {
			if(!v[i]) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1450D
		
		//notice that excluding 1, if a length k works, then length k + 1 will also work. Thus we can binary search to find the minimum value of k that will work, excluding 1. We need to check 1 
		//separately
		
		//to check, use two pointer method to find the minimum within range, using two stacks.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int high = n;
			int low = 2;
			int mid = low + (high - low) / 2;
			int ans = n + 1;
			while(low <= high) {
				if(isValid(nums, mid)) {
					ans = Math.min(mid, ans);
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			for(int i = 0; i < n; i++) {
				if(i == 0) {
					if(isValid(nums, 1)) {
						fout.append(1);
					}
					else {
						fout.append(0);
					}
				}
				else {
					fout.append((i + 1 >= ans)? 1 : 0);
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
