package chefmonocarp;

import java.util.*;
import java.io.*;

public class chefmonocarp {
	public static void main(String[] args) throws IOException {
		
		//1437C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int q = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			Integer[] nums = new Integer[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			int[] v = new int[n * 2 + 10];
			Arrays.fill(v, -1);
			for(int i = 0; i < n; i++) {
				int next = nums[i];
				int pointer = 0;
				while(v[next + pointer] != -1) {
					pointer ++;
				}
				v[next + pointer] = i;
			}
			while(true) {
				boolean changes = false;
				for(int i = 0; i < v.length; i++) {
					if(v[i] != -1 && nums[v[i]] != i) {
						Queue<int[]> queue = new ArrayDeque<int[]>();
						int pointer = i;
						while(pointer != 0 && v[pointer - 1] != -1) {
							pointer --;
						}
						int start = pointer - 1;
						int oldCost = 0;
						while(pointer != v.length - 1 && v[pointer] != -1) {
							queue.add(new int[] {nums[v[pointer]], v[pointer]});
							oldCost += Math.abs(nums[v[pointer]] - pointer);
						}
						int end = pointer;
						pointer = start;
						int newCost = 0;
						while(queue.size() != 0) {
							
						}
					}
				}
			}
		}
	}
}
