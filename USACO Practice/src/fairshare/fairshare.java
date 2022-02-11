package fairshare;

import java.util.*;
import java.io.*;

public class fairshare {
	public static void main(String[] args) throws IOException {
		
		//1634E
		
		//i thought it would be a greedy solution. i was wrong
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int m = Integer.parseInt(fin.readLine());
		int[][] nums = new int[m][];
		HashMap<Integer, Integer> count = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> cur = new HashMap<Integer, Integer>();
		boolean isValid = true;
		char[][] ans = new char[m][];
		for(int i = 0; i < m; i++) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			nums[i] = new int[n];
			ans[i] = new char[n];
			if(n % 2 == 1) {
				isValid = false;
			}
			for(int j = 0; j < n; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
				count.put(nums[i][j], count.getOrDefault(nums[i][j], 0) + 1);
				ans[i][j] = j < (n / 2)? 'L' : 'R';
				if(ans[i][j] == 'L') {
					cur.put(nums[i][j], cur.getOrDefault(nums[i][j], 0) + 1);
				}
			}
		}
		for(int i : count.values()) {
			if(i % 2 == 1) {
				isValid = false;
				break;
			}
		}
		if(!isValid) {
			System.out.println("NO\n");
			return;
		}
		System.out.print("YES\n");
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < m; i++) {
			int less = 0;
			int greater = 0;
			//System.out.println(i);
			outer:
			while(true) {
				while(cur.getOrDefault(nums[i][less], 0) >= count.get(nums[i][less]) / 2) {
					less ++;
					if(less == nums[i].length) {
						break outer;
					}
				}
				while(cur.getOrDefault(nums[i][greater], 0) <= count.get(nums[i][greater]) / 2) {
					greater ++;
					if(greater == nums[i].length) {
						break outer;
					}
				}
				if(ans[i][less] == 'R' && ans[i][greater] == 'L') {
					ans[i][greater] = 'R';
					ans[i][less] = 'L';
					//System.out.println(String.valueOf(ans[i]) + " " + less + " " + greater);
					cur.put(nums[i][greater], cur.get(nums[i][greater]) - 1);
					cur.put(nums[i][less], cur.getOrDefault(nums[i][less], 0) + 1);
				}
				less ++;
				greater ++;
				if(less == nums[i].length || greater == nums[i].length) {
					break;
				}
			}
		}
		for(int i = 0; i < m; i++) {
			fout.append(String.valueOf(ans[i])).append("\n");
		}
		System.out.print(fout);
	}
}
