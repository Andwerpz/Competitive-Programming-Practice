//package dzylovessequences;

import java.util.*;
import java.io.*;

public class dzylovessequences {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		ArrayList<ArrayList<Integer>> segments = new ArrayList<ArrayList<Integer>>(); //stores the contents of each strictly increasing segment
		segments.add(new ArrayList<Integer>());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			if(i != 0) {
				if(nums[i - 1] < nums[i]) {
					segments.get(segments.size() - 1).add(nums[i]);
				}
				else {
					segments.add(new ArrayList<Integer>());
					segments.get(segments.size() - 1).add(nums[i]);
				}
			}
			else {
				segments.get(segments.size() - 1).add(nums[i]);
			}
		}
		
		int ans = segments.get(0).size() + (segments.size() >= 2? 1 : 0);
		for(int i = 0; i < segments.size() - 1; i++) {
			int a = segments.get(i).get(segments.get(i).size() - 1);
			int b = -1;
			if(segments.get(i + 1).size() >= 2) {
				b = segments.get(i + 1).get(1);
			}
			if(b - a >= 2) {
				ans = Math.max(segments.get(i).size() + segments.get(i + 1).size(), ans);
			}
			a = Integer.MAX_VALUE;
			b = segments.get(i + 1).get(0);
			if(segments.get(i).size() >= 2) {
				a = segments.get(i).get(segments.get(i).size() - 2);
			}
			if(b - a >= 2) {
				ans = Math.max(segments.get(i).size() + segments.get(i + 1).size(), ans);
			}
			ans = Math.max(segments.get(i + 1).size() + 1, ans);
		}
		System.out.println(ans);
	}
}
