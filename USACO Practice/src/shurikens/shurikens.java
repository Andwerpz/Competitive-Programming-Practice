//package shurikens;

import java.util.*;
import java.io.*;

public class shurikens {
	
	static PriorityQueue<int[]> nums;	//number that numbers are above, quantity of numbers that are above
	
	public static void main(String[] args) throws IOException {
		
		//1413D
		
		//when a ninja buys a shuriken, then you know that all remaining shurikens are greater than the price that they bought it for. If a ninja buys a shuriken
		//and you don't have any record of shurikens being less that that price, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		nums = new PriorityQueue<int[]>((a, b) -> a[0] - b[0]);
		int[] ans = new int[n];
		Arrays.fill(ans, -1);
		TreeSet<Integer> v = new TreeSet<Integer>();
		for(int i = 0; i < n; i++) {
			v.add(i + 1);
		}
		int wildcards = 0;
		boolean isValid = true;
		int pointer = -1;
		int tempPointer = -1;
		boolean validPlacement = true;
		for(int i = 0; i < n * 2; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			String which = st.nextToken();
			if(which.equals("+")) {
				wildcards ++;
				pointer ++;
				tempPointer = pointer;
				validPlacement = true;
			}
			else {
				int next = Integer.parseInt(st.nextToken());
				while(tempPointer >= 0 && ans[tempPointer] != -1) {
					tempPointer --;
				}
				if(tempPointer < 0) {
					isValid = false;
					break;
				}
				else if(validPlacement){
					ans[tempPointer] = next;
					tempPointer --;
					v.remove(next);
				}
				
				
				
				if(nums.size() == 0) {
					if(wildcards == 0) {
						isValid = false;
						break;
					}
					else if(wildcards != 1){
						nums.add(new int[] {next, wildcards - 1});
					}
					wildcards = 0;
				}
				else {
					if(nums.peek()[0] >= next) {
						if(wildcards == 0) {
							isValid = false;
							break;
						}
						else if(wildcards != 1) {
							nums.add(new int[] {next, wildcards - 1});
						}
						wildcards = 0;
					}
					else {
						int cur = wildcards;
						wildcards = 0;
						while(nums.size() != 0 && nums.peek()[0] < next) {
							cur += nums.poll()[1];
						}
						nums.add(new int[] {next, cur - 1});
					}
				}
			}
		}
		if(isValid) {
			System.out.println("YES");
			StringBuilder fout = new StringBuilder();
			for(int i = 0; i < n; i++) {
				//System.out.print(ans[i]);
				if(ans[i] == -1) {
					ans[i] = v.pollLast();
				}
				fout.append(ans[i]).append(" ");
			}
			System.out.println(fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
