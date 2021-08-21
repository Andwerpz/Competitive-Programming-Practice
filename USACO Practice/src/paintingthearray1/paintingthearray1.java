//package paintingthearray1;

import java.util.*;
import java.io.*;

public class paintingthearray1 {
	public static void main(String[] args) throws IOException {
		
		//1479B1
		
		//greedy solution: save two numbers, the previous number picked for color 0 and color 1. Consider the next number to be picked. If the next number is equal to one number, but not equal to the other, 
		//replace the unequal number. If the next number is equal to both numbers, then you can't do anything. If the next number is unequal to both numbers, then from the two numbers, replace the number
		//that reoccurs the first out of the two previous pointers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		ArrayList<ArrayDeque<Integer>> dict = new ArrayList<ArrayDeque<Integer>>();
		for(int i = 0; i < n; i++) {
			dict.add(new ArrayDeque<Integer>());
		}
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			nums[i] = next;
			dict.get(next).add(i);
		}
		int prev0 = -1;
		int prev1 = -1;
		int ans = 0;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			dict.get(next).poll();
			if(prev0 != next && prev1 != next) {
				int dist0 = 0;
				int dist1 = 0;
				if(prev0 != -1) {
					dist0 = dict.get(prev0).peek() == null? n + 1 : dict.get(prev0).peek();
				}
				if(prev1 != -1) {
					dist1 = dict.get(prev1).peek() == null? n + 1 : dict.get(prev1).peek();
				}
				int distNext = dict.get(next).peek() == null? n + 1 : dict.get(next).peek();
				if(prev0 == -1 && prev1 == -1) {
					prev0 = next;
					ans ++;
				}
				else if(prev0 == -1) {
					if(distNext > dist1) {
						prev1 = next;
						ans ++;
					}
					else {
						prev0 = next;
						ans ++;
					}
				}
				else if(prev1 == -1) {
					if(distNext > dist0) {
						prev0 = next;
						ans ++;
					}
					else {
						prev1 = next;
						ans ++;
					}
				}
				else {
					
					if(dist0 < dist1) {
						prev0 = next;
						ans ++;
					}
					else {
						prev1 = next;
						ans ++;
					}
				}
			}
			else if(prev0 != next) {
				prev0 = next;
				ans ++;
			}
			else if(prev1 != next) {
				prev1 = next;
				ans ++;
			}
			//System.out.println((prev0 + 1) + " " + (prev1 + 1));
		}
		System.out.println(ans);
	}
}
