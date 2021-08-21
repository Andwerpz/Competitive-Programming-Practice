//package strangelist;

import java.util.*;
import java.io.*;

public class strangelist {
	public static void main(String[] args) throws IOException {
		
		//1471B
		
		//For each number, find out how many times x can go into them cleanly. Then, find the first number with the minimum amount of times. Add to the sum, every number multiplied by the minimum amount of times
		//and for the numbers before the minimum, the number * minimum + 1.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			long sum = 0;
			st = new StringTokenizer(fin.readLine());
			long[] nums = new long[n];
			int minPower = Integer.MAX_VALUE;
			int minIndex = 0;
			for(int i = 0; i < n; i++) {
				long next = Integer.parseInt(st.nextToken());
				nums[i] = next;
				int power = 0;
				while(next % x == 0) {
					power ++;
					next /= x;
				}
				if(minPower > power) {
					minIndex = i;
				}
				minPower = Math.min(power, minPower);
			}
			for(int i = 0; i < n; i++) {
				if(i < minIndex) {
					sum += ((long) minPower + 2) * nums[i];
				}
				else {
					sum += ((long) minPower + 1) * nums[i];
				}
			}
			fout.append(sum).append("\n");
		}
		System.out.print(fout);
	}
}
