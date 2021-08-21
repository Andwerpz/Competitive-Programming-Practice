//package creativesnap;

import java.util.*;
import java.io.*;

public class creativesnap {
	
	static int k, a, b;
	static int[] nums;
	
	public static int getAns(int l, int r) {
		//System.out.println(l + " " + r);
		int sum = 0;
		for(int i = l; i <= r; i++) {
			sum += nums[i];
		}
		if(sum == 0) {
			return a;
		}
		else if(r == l) {
			return sum * b;
		}
		else {
			return Math.min(sum * b * ((r - l) + 1), getAns(l, l + (r - l) / 2) + getAns(l + (r - l) / 2 + 1, r));
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1111C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		a = Integer.parseInt(st.nextToken());
		b = Integer.parseInt(st.nextToken());
		//nums = new int[(int) Math.pow(2, n)];
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < k; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			//nums[next] ++;
		}
		ArrayList<ArrayList<Integer>> dp = new ArrayList<ArrayList<Integer>>();
		int increment = 1;
		int curCost = 0;
		int layer = 0;
		while(increment <= nums.length) {
			dp.add(new ArrayList<Integer>());
			for(int i = 0; i < nums.length; i++) {
				curCost += nums[i] * increment;
				if((i + 1) % increment == 0) {
					int minCost = curCost;
					if(curCost == 0) {
						//System.out.println("ADD");
						minCost += a;
					}
					else {
						minCost *= b;
					}
					if(layer != 0) {
						int size = dp.get(layer).size();
						int a = dp.get(layer - 1).get(size * 2);
						int b = dp.get(layer - 1).get(size * 2 + 1);
						minCost = Math.min(minCost, a + b);
					}
					dp.get(layer).add(minCost);
					curCost = 0;
				}
			}
			//System.out.println(dp);
			increment *= 2;
			layer ++;
		}
		//System.out.println(dp);
		System.out.println(dp.get(dp.size() - 1).get(0));
	}
}
