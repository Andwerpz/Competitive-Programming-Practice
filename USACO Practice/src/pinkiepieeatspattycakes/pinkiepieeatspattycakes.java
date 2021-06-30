//package pinkiepieeatspattycakes;

import java.util.*;
import java.io.*;

public class pinkiepieeatspattycakes {
	public static void main(String[] args) throws IOException {
		
		//1393C
		
		//i don't really understand the math to calculate the answer. 
		//basically we have to find the maximum amount of times any number repeats, and the amount of numbers that repeat the maximum.
		
		//There is an binary search solution where you set the minimum distance between any two same number. I understand that, but i don't understand how to put the 
		//numbers in order when checking whether a given minimum is valid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashMap<Integer, Integer> nums = new HashMap<Integer, Integer>();
			int max = 0;
			int maxFreq = 0;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				nums.put(next, nums.getOrDefault(next, 0) + 1);
				if(nums.get(next) == max) {
					maxFreq ++;
				}
				else if(nums.get(next) > max){
					maxFreq = 1;
				}
				max = Math.max(nums.get(next), max);	
			}
			int ans = (n - maxFreq) / (max - 1) - 1;
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
