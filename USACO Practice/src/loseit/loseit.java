//package loseit;

import java.util.*;
import java.io.*;

public class loseit {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		ArrayList<Queue<Integer>> loc = new ArrayList<Queue<Integer>>();
		for(int i = 0; i < 6; i++) {
			loc.add(new ArrayDeque<Integer>());
		}
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			if(next == 4) {
				nums[i] = 0;
				loc.get(0).add(i);
			}
			else if(next == 8) {
				nums[i] = 1;
				loc.get(1).add(i);
			}
			else if(next == 15) {
				nums[i] = 2;
				loc.get(2).add(i);
			}
			else if(next == 16) {
				nums[i] = 3;
				loc.get(3).add(i);
			}
			else if(next == 23) {
				nums[i] = 4;
				loc.get(4).add(i);
			}
			else {
				nums[i] = 5;
				loc.get(5).add(i);
			}
		}
		int sum = 0;
		while(true) {
			boolean isValid = true;
			boolean done = false;
			int index = -1;
			for(int i = 0; i < 6; i++) {
				if(loc.get(i).size() == 0) {
					done = true;
					break;
				}
				if(loc.get(i).peek() < index) {
					isValid = false;
					loc.get(i).poll();
					break;
				}
				else {
					index = loc.get(i).peek();
				}
			}
			if(done) {
				break;
			}
			if(isValid) {
				sum += 6;
				for(int i = 0; i < 6; i++) {
					loc.get(i).poll();
				}
			}
		}
		System.out.println(n - sum);
	}
}
