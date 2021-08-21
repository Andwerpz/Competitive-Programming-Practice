//package carousel;

import java.util.*;
import java.io.*;

public class carousel {
	public static void main(String[] args) throws IOException {
		
		//1328D
		
		//you just have to check the graph for bipartitness. You can go with an easier greedy solution though: 
		
		//section the array off into groups of adjacent identical numbers. alternate between the colors; first group gets 1, second gets 2, third gets 1, and so on. If you have only 1 group,
		//then you only need 1 color, and you're done. If you have an even amount of groups, then you only need two colors as it is guaranteed that the last group will be of a different color than the 
		//first group. Now, if you have an odd amount of groups, then you need to check the last group and the first group. If they are of the same type, then you only need two colors. But if they are of
		//different types, check if you have any repeating numbers within your array. If you do, you can just reverse the color of all numbers after the second repeated number
		//and you should only need two colors. But if you don't have any repeating numbers, then you have to color either the last group or the first group a third color, resulting in you needing
		//3 colors.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int q = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			int[] ans = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int prev = 0;
			int max = 1;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(i == 0) {
					ans[0] = 1;
				}
				else {
					ans[i] = ans[i - 1];
				}
				if(i != 0 && nums[i] != prev) {
					if(ans[i] == 1) {
						ans[i] = 2;
						max = 2;
					}
					else {
						ans[i] = 1;
					}
				}
				prev = nums[i];
			}
			if(ans[n - 1] == ans[0] && nums[n - 1] != nums[0]) {
				boolean isValid = false;
				for(int i = 1; i < n; i++) {
					if(nums[i - 1] == nums[i]) {
						isValid = true;
						for(int j = i; j < n; j++) {
							if(ans[j] == 1) {
								ans[j] = 2;
							}
							else {
								ans[j] = 1;
							}
						}
						break;
					}
				}
				if(!isValid) {
					int pointer = n - 1;
					max = 3;
					while(ans[pointer] == 1) {
						ans[pointer] = 3;
						pointer --;
					}
				}
			}
			fout.append(max).append("\n");
			for(int i = 0; i < ans.length; i++) {
				fout.append(ans[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
