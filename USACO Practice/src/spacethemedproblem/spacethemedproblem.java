package spacethemedproblem;

import java.util.*;
import java.io.*;

public class spacethemedproblem {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		HashSet<Integer> nums = new HashSet<Integer>();
		for(int i = 0; i < n; i++) {
			nums.add(Integer.parseInt(st.nextToken()));
		}
		StringBuilder fout = new StringBuilder();
		int counter = 0;
		for(int i = 1; i <= 100; i++) {
			if(!nums.contains(i)) {
				counter ++;
				fout.append(i).append(" ");
			}
		}
		System.out.println(counter);
		System.out.println(fout);
	}
}
