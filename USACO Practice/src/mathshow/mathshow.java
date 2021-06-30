//package mathshow;

import java.util.*;
import java.io.*;

public class mathshow {
	
	static int[] nums;
	
	public static void main(String[] args) throws IOException {
		
		//846B
		
		//you can brute force this. 
		//first, assume that you solve i problems completely. you can then proceed to maximize your score without solving any more problems completely by then prioritizing subtasks. 
		//you must prioritize the subtasks that have the minimum cost associated with them. If you iterate i from 0 - n, then the maximum should be the maximum score that you can
		//achieve.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nums = new int[k];
		st = new StringTokenizer(fin.readLine());
		int completeSolveCost = 0;
		for(int i = 0; i < k; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			completeSolveCost += nums[i];
		}
		Arrays.sort(nums);
		int ans = 0;
		for(int i = 0; i <= n; i++) {	//the number of tasks we completely solve.
			int cur = 0;
			int time = m;
			if(completeSolveCost * i <= time) {
				//System.out.println("UES");
				time -= completeSolveCost * i;
				cur += (nums.length + 1) * i;
				int tasksRemaining = n - i;
				for(int j = 0; j < k; j++) {
					int taskCost = nums[j];
					if(taskCost * tasksRemaining <= time) {
						time -= taskCost * tasksRemaining;
						cur += tasksRemaining;
					}
					else {
						//System.out.println(time + " " + taskCost);
						cur += time / taskCost;
						break;
					}
				}
			}
			ans = Math.max(ans, cur);
		}
		System.out.println(ans);
	}
}
