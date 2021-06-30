//package equalizethearray;

import java.util.*;
import java.io.*;

public class equalizethearray {
	public static void main(String[] args) throws IOException {
		
		//1490F
		
		//try out every c value from max to 0. You can try out every c value in constant time if you keep a running total of how many numbers you have to remove 
		//to get the previous c value. If you test a c value and there are values equal to this c value, subtract all of them from the running total, and for every step
		//if there are values above the c value you test, then add 1 for each.
		
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
			Arrays.sort(nums);
			TreeMap<Integer, Integer> dict = new TreeMap<Integer, Integer>();	//for any amount quantity of numbers, store the amount of unique numbers that have that quantity
			int maxSame = 0;
			int prev = nums[0];
			int sum = 0;
			for(int i = 0; i < n; i++) {
				if(prev == nums[i]) {
					sum ++;
				}
				else {
					maxSame = Math.max(maxSame, sum);
					dict.put(sum, dict.getOrDefault(sum, 0) + 1);
					prev = nums[i];
					sum = 1;
				}
			}
			dict.put(sum, dict.getOrDefault(sum, 0) + 1);
			maxSame = Math.max(maxSame, sum);
			int ans = Integer.MAX_VALUE;
			sum = n;	//now storing the number of nums
			int numAbove = 0;
			for(int i = maxSame + 1; i >= 0; i--) {
				sum += numAbove;
				int numCur = dict.getOrDefault(i, 0);
				numAbove += numCur;
				sum -= numCur * i;
				ans = Math.min(ans, sum);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
