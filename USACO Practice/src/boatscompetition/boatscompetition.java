//package boatscompetition;

import java.util.*;
import java.io.*;

public class boatscompetition {
	public static void main(String[] args) throws IOException {
		
		//1399C
		
		//brute force.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int ans = 0;
			for(int i = 2; i <= n * 2; i++) {
				HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
				int curAns = 0;
				for(int j = 0; j < n; j++) {
					int next = nums[j];
					if(next < i && dict.containsKey(i - next)) {
						curAns ++;
						dict.put(i - next, dict.get(i - next) - 1);
						if(dict.get(i - next) == 0) {
							dict.remove(i - next);
						}
					}
					else {
						dict.put(next, dict.getOrDefault(next, 0) + 1);
					}
				}
				ans = Math.max(curAns, ans);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
