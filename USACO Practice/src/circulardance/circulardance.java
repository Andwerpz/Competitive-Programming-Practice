//package circulardance;

import java.util.*;
import java.io.*;

public class circulardance {
	public static void main(String[] args) throws IOException {
		
		//1095D
		
		//first, start with any kid. Then take a look at the people that he remembers. If one person that he remembers, remembers the other person that he remembers, 
		//then that person is the one that comes right after this kid. Else, the other kid comes right after. Repeat n times.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] nums = new int[n][2];	//the ids that each kid remembers
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			nums[i][0] = Integer.parseInt(st.nextToken()) - 1;
			nums[i][1] = Integer.parseInt(st.nextToken()) - 1;
		}
		int pointer = 0;
		StringBuilder fout = new StringBuilder();
		fout.append(pointer + 1).append(" ");
		HashSet<Integer> v = new HashSet<Integer>();
		v.add(pointer);
		for(int i = 1; i < n; i++) {
			HashSet<Integer> next = new HashSet<Integer>();
			next.add(nums[pointer][0]);
			next.add(nums[pointer][1]);
			int nextId = nums[pointer][0];
			if((next.contains(nums[nextId][0]) || next.contains(nums[nextId][1])) && !v.contains(nextId)) {
				pointer = nextId;
			}
			else {
				pointer = nums[pointer][1];
			}
			v.add(pointer);
			fout.append(pointer + 1).append(" ");
		}
		System.out.println(fout);
	}
}
