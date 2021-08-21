//package carrotsforrabbits;

import java.util.*;
import java.io.*;	


public class carrotsforrabbits {
	
	public static long getCost(long a, long val) {
		long remainder = a % val;
		a -= remainder;
		long multiple = a / val;
		long ans = (multiple * multiple) * (val - remainder);
		ans += ((long) Math.pow(multiple + 1, 2)) * remainder;
		return ans;
	}
	
	public static long getDecrease(long[] a) {
		return getCost(a[0], a[1] + 1) - getCost(a[0], a[1]);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1428E
		
		//this solution is actually genius
		
		//we can distribute our carrot splits onto the carrots we already have to make them shorter. We have k - n splits available to us. Notice that the more splits we spend on a single carrot, 
		//the less return we get in terms of saved time. This means that after we spend our first split, we then need to go and find the new maximum return for the next split. This can easily
		//be done with a priority queue sorting by the amount of return when the next split is spent on that given carrot.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		long ans = 0;
		long[] nums = new long[n];
		PriorityQueue<long[]> q = new PriorityQueue<long[]>((a, b) -> Long.compare(getDecrease(a), getDecrease(b)));
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			ans += nums[i] * nums[i];
			q.add(new long[] {nums[i], 1});
		}
		for(int i = 0; i < k - n; i++) {
			long[] next = q.poll();
			ans += getDecrease(next);
			next[1] ++;
			q.add(next);
		}
		System.out.println(ans);
	}
}
