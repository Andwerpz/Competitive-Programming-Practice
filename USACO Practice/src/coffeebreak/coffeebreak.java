//package coffeebreak;

import java.util.*;
import java.io.*;

public class coffeebreak {
	public static void main(String[] args) throws IOException {
		
		//1041C
		
		//each day, you want to maximize the amount of coffee breaks you take, to spend the minimum amount of days. To do this easily, you can binary search for the next coffee break, or use a tree
		//like data structure. In java, use TreeSet.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		TreeSet<Integer> nums = new TreeSet<Integer>();
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		int[] order = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			nums.add(next);
			order[i] = next;
		}
		int ans = 0;
		while(nums.size() != 0) {
			ans ++;
			int pointer = nums.first();
			nums.remove(pointer);
			dict.put(pointer, ans);
			while(nums.ceiling(pointer + d + 1) != null) {
				pointer = nums.ceiling(pointer + d + 1);
				nums.remove(pointer);
				dict.put(pointer, ans);
			}
		}
		StringBuilder fout = new StringBuilder();
		fout.append(ans).append("\n");
		for(int i = 0; i < order.length; i++) {
			fout.append(dict.get(order[i])).append(" ");
		}
		System.out.println(fout);
	}
}
