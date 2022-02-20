//package avoidlocalmaximums;

import java.util.*;
import java.io.*;

public class avoidlocalmaximums {
	public static void main(String[] args) throws IOException {
		
		//1635B
		
		//getting rid of one maximum will take 1 move: make the maximum equal to the maximum
		//of it's adjacent numbers. This will also guarantee to not make a new maximum
		
		//notice that if there are two maximums separated by one number, then you can remove both of 
		//them in one operation: make the seperating number equal to the maximum of the two maximums. 
		
		//thus, to solve, just split the array into sequences of adjacent maximums, and greedily
		//remove 2 at a time, until you can't, then remove 1 at a time.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			ArrayList<Integer> max = new ArrayList<Integer>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			for(int i = 1; i < n - 1; i++) {
				if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
					max.add(i);
				}
			}
			int ans = 0;
			for(int i = 0; i < max.size(); i++) {
				int cur = max.get(i);
				if(i != max.size() - 1) {
					int next = max.get(i + 1);
					if(cur + 2 == next) {
						ans ++;
						nums[cur + 1] = Math.max(nums[cur], nums[next]);
						i ++;
						continue;
					}
				}
				ans ++;
				nums[cur] = Math.max(nums[cur - 1], nums[cur + 1]);
			}
			fout.append(ans).append("\n");
			for(int i : nums) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
