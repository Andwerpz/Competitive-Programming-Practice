//package multisubjectcompetition;

import java.util.*;
import java.io.*;

public class multisubjectcompetition {
	public static void main(String[] args) throws IOException {
		
		//1082C
		
		//sort everyone into groups based on their specialization subject. If everyone has a negative value, then return 0.
		//Once you have them in groups, sort them in descending order based on skill level, and then start trying different group sizes, from 1 - max group size. 
		//To make this faster, you can construct a pfx sum for each specialization, and get sums that way.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> nums = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < m; i++) {
			nums.add(new ArrayList<Integer>());
		}
		boolean isValid = false;
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int subject = Integer.parseInt(st.nextToken()) - 1;
			int level = Integer.parseInt(st.nextToken());
			if(level >= 0) {
				isValid = true;
			}
			nums.get(subject).add(level);
		}
		if(isValid) {
			nums.sort((a, b) -> -Integer.compare(a.size(), b.size()));
			for(ArrayList<Integer> i : nums) {
				i.sort((a, b) -> -Integer.compare(a, b));
			}
			for(ArrayList<Integer> i : nums) {
				for(int j = 1; j < i.size(); j++) {
					i.set(j, i.get(j - 1) + i.get(j));
				}
			}
			int maxSize = nums.get(0).size();
			int max = 0;
			for(int i = 1; i <= maxSize; i++) {
				int cur = 0;
				for(int j = 0; j < nums.size(); j++) {
					if(nums.get(j).size() < i) {
						break;
					}
					cur += nums.get(j).get(i - 1) > 0? nums.get(j).get(i - 1) : 0;
				}
				max = Math.max(cur, max);
			}
			System.out.println(max);
		}
		else {
			System.out.println("0");
		}
	}
}
