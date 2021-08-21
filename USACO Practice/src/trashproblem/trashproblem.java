//package trashproblem;

import java.util.*;
import java.io.*;

public class trashproblem {
	public static void main(String[] args) throws IOException {
		
		//1418D
		
		//given a set of trash piles, notice that the minimum amount of moves to put all the trash into two piles is equal to the range of the piles, minus the range of the largest gap in the piles. 
		//if we keep track of those two values when updating, we can get our answer quickly for each query. 
		
		//to keep track of the range, all we have to do is maintain a tree set. When we want to query the range, just retrieve the first and last values in the tree. 
		
		//largest gap is harder. we can have a tree map that keeps track of the number of occurrences of each length of gap. When we add a pile, if the pile is in between two existing piles, we add two new 
		//gaps, and take away the old one that we removed due to adding the pile. When we take away a pile, we have to take away two gaps, and add a new gap equal to the sum of the two gaps. To query the
		//answer, just take the largest key in the map.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		TreeSet<Integer> dict = new TreeSet<Integer>();
		TreeMap<Integer, Integer> diff = new TreeMap<Integer, Integer>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			dict.add(next);
		}
		int prev = dict.first();
		Integer next = dict.ceiling(prev + 1);
		while(next != null) {
			//System.out.println(prev + " " + next);
			int nextDiff = next - prev;
			diff.put(nextDiff, diff.getOrDefault(nextDiff, 0) + 1);
			prev = next;
			next = dict.ceiling(prev + 1);
		}
		StringBuilder fout = new StringBuilder();
		int ans = 0;
		if(diff.size() != 0) {
			ans = (dict.last() - dict.first()) - diff.lastKey();
		}
		fout.append(ans).append("\n");
		while(q-- > 0) {
			//System.out.println(q);
			st = new StringTokenizer(fin.readLine());
			int which = Integer.parseInt(st.nextToken());
			int index = Integer.parseInt(st.nextToken());
			Integer r = dict.ceiling(index + 1);
			Integer l = dict.floor(index - 1);
			int rDiff = 0;
			int lDiff = 0;
			int nextDiff = 0;
			if(r != null) {
				rDiff = r - index;
			}
			if(l != null) {
				lDiff = index - l;
			}
			if(r != null && l != null) {
				nextDiff = r - l;
			}
			if(which == 0) {
				if(r != null) {
					diff.put(rDiff, diff.get(rDiff) - 1);
					if(diff.get(rDiff) == 0) {
						diff.remove(rDiff);
					}
				}
				if(l != null) {
					diff.put(lDiff, diff.get(lDiff) - 1);
					if(diff.get(lDiff) == 0) {
						diff.remove(lDiff);
					}
				}
				if(r != null && l != null) {
					diff.put(nextDiff, diff.getOrDefault(nextDiff, 0) + 1);
				}
				dict.remove(index);
			}
			else {
				if(r != null) {
					diff.put(rDiff, diff.getOrDefault(rDiff, 0) + 1);
				}
				if(l != null) {
					diff.put(lDiff, diff.getOrDefault(lDiff, 0) + 1);
				}
				if(r != null && l != null) {
					diff.put(nextDiff, diff.get(nextDiff) - 1);
					if(diff.get(nextDiff) == 0) {
						diff.remove(nextDiff);
					}
				}
				dict.add(index);
			}
			ans = 0;
			if(diff.size() != 0) {
				ans = (dict.last() - dict.first()) - diff.lastKey();
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
