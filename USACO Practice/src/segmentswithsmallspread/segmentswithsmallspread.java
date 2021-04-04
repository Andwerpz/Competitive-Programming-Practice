//package segmentswithsmallspread;

import java.io.*;
import java.util.*;

public class segmentswithsmallspread {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long k = Long.parseLong(st.nextToken());
		long[] nums = new long[n];
		long ans = 0;
		Stack<long[]> s1 = new Stack<long[]>();	//forward stack
		Stack<long[]> s2 = new Stack<long[]>();	//back stack
		int low = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Long.parseLong(st.nextToken());
			if(s1.size() == 0) {
				s1.push(new long[] {nums[i], nums[i], nums[i]});
			}
			else {
				s1.push(new long[] {nums[i], Math.max(nums[i], s1.peek()[1]), Math.min(nums[i], s1.peek()[2])});
			}
			//System.out.println(s1.peek()[1] + " " + s1.peek()[2]);
			long min = s1.peek()[2];
			long max = s1.peek()[1];
			if(s2.size() != 0) {
				min = Math.min(min, s2.peek()[2]);
				max = Math.max(max, s2.peek()[1]);
			}
			if(s2.size() == 0 && max - min > k) {
				//System.out.println("refilling s2");
				while(s1.size() != 0) {	//when refilling the second stack, you can't directly pop the stuff from the first stack to the second.
					//you need to reprocess all of the numbers so you effectively make a suffix min, max list.
					long[] next = s1.pop();
					if(s2.size() == 0) {
						s2.push(new long[] {next[0], next[0], next[0]});
					}
					else {
						s2.push(new long[] {next[0], Math.max(next[0], s2.peek()[1]), Math.min(next[0], s2.peek()[2])});
					}
				}
			}
			while(max - min > k) {
				
				s2.pop();
				low++;
				//System.out.println("pop " + max + " " + min + " " + s1.size() + " " + s2.size());
				if(s1.size() != 0 && s2.size() == 0) {
					min = s1.peek()[2];
					max = s1.peek()[1];
				}
				else if(s2.size() != 0 && s1.size() == 0) {
					//System.out.println("setting max and min");
					min = s2.peek()[2];
					max = s2.peek()[1];
					//System.out.println("set to " + max + " " + min);
				}
				else if(s2.size() == 0 && s1.size() == 0) {
					max = 0;
					min = 0;
				}
				else {
					//System.out.println(s1.size() + " " + s2.size());
					min = Math.min(s1.peek()[2], s2.peek()[2]);
					max = Math.max(s1.peek()[1], s2.peek()[1]);
				}
				if(s2.size() == 0) {
					while(s1.size() != 0) {
						long[] next = s1.pop();
						if(s2.size() == 0) {
							s2.push(new long[] {next[0], next[0], next[0]});
						}
						else {
							s2.push(new long[] {next[0], Math.max(next[0], s2.peek()[1]), Math.min(next[0], s2.peek()[2])});
						}
					}
				}
			}
			ans += i - low + 1;
			//System.out.println(i + " " + (max - min));
		}
		System.out.println(ans);
	}
}
