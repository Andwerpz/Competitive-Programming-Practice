//package sumofthreevalues;

import java.util.*;
import java.io.*;

public class sumofthreevalues {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			dict.put(nums[i], i);
		}
		//Arrays.sort(nums);
		boolean done = false;
		for(int i = 0; i < n; i++) {
			int cur = nums[i];
			for(int j = 0; j < n; j++) {
				int next = nums[j];
				if(dict.containsKey(x - (next + cur)) && i != j && dict.get(x - (next + cur)) != j && dict.get(x - (next + cur)) != i) {
					System.out.println((dict.get(x - (next + cur)) + 1) + " " + (i + 1) + " " + (j + 1));
					done = true;
					break;
				}
			}
			if(done) {
				break;
			}
		}
		if(!done) {
			System.out.println("IMPOSSIBLE");
		}
	}
}
