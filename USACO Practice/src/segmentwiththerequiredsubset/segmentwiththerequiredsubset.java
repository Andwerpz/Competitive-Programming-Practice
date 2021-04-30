package segmentwiththerequiredsubset;

import java.util.*;
import java.io.*;

public class segmentwiththerequiredsubset {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int s = Integer.parseInt(st.nextToken());
		int low = 0;
		int sum = 0;
		int[] nums = new int[n];
		int min = Integer.MAX_VALUE;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
			
			//System.out.println(sum);
			while(sum > s) {
				sum -= nums[low];
				low ++;
			}
			System.out.println(low + " " + i + " " + sum);
			if(s == sum ) {
				min = Math.min(min, i - low + 1);
			}
		}
		System.out.println(min);
	}
}
