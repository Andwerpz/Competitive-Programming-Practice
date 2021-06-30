package berlandcrossword;

import java.util.*;
import java.io.*;

public class berlandcrosswordver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int[] nums = new int[4];
			boolean[] actions = new boolean[4];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			for(int i = 0; i < 4; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			boolean twos = false;
			for(int i = 0; i < nums.length; i++) {
				if(nums[i] == n) {
					twos = true;
				}
			}
			boolean done = false;
			while(!done) {
				done = true;
				for(int i = 4; i < 8; i++) {
					if (nums[i % 4] > n - 2 && nums[(i + 1) % 4] > 0 && !actions[i % 4]) {
						if(twos && nums[i % 4] == n) {
							nums[i % 4] --;
							nums[(i + 1) % 4] --;
							done = false;
							actions[i % 4] = true;
						}
						else if(!twos){
							nums[i % 4] --;
							nums[(i + 1) % 4] --;
							done = false;
							actions[i % 4] = true;
						}
					}
					if (nums[i % 4] > n - 2 && nums[(i - 1) % 4] > 0 && !actions[(i - 1) % 4]) {
						if(twos && nums[i % 4] == n) {
							nums[i % 4] --;
							nums[(i - 1) % 4] --;
							done = false;
							actions[(i - 1) % 4] = true;
						}
						else if(!twos){
							nums[i % 4] --;
							nums[(i - 1) % 4] --;
							done = false;
							actions[(i - 1) % 4] = true;
						}
					}
				}
				for(boolean i : actions) {
					System.out.println(i);
				}
				for(int i : nums) {
					System.out.print(i + " ");
				}
				System.out.println();
				System.out.println();
				twos = false;
			}
//			for(boolean i : actions) {
//				System.out.println(i);
//			}
			boolean isValid = true;
			for(int i = 0; i < 4; i++) {
				//System.out.println(nums[i]);
				if(nums[i] > n - 2) {
					isValid = false;
				}
			}
			fout.append(isValid? "YES" : "NO").append("\n");
		}
		System.out.print(fout);
	}
}
