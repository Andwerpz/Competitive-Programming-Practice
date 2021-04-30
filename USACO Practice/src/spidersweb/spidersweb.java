//package spidersweb;

import java.util.*;
import java.io.*;

public class spidersweb {
	
	public static int binarySearch(int l, int h, ArrayList<Integer> nums) {
		int low = 0;
		int high = nums.size() - 1;
		int mid = low + (high - low) / 2;
		int ansLow = -1;
		int ansHigh = -1;
		while(low <= high) {
			if(nums.get(mid) < l) {
				low = mid + 1;
				if(ansLow < mid || ansLow == -1) {
					ansLow = mid;
				}
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		low = 0;
		high = nums.size() - 1;
		mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums.get(mid) > h) {
				high = mid - 1;
				if(ansHigh > mid || ansHigh == -1) {
					ansHigh = mid;
				}
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		//System.out.println(ansLow + " " + ansHigh);
		if(ansLow == -1 && ansHigh == -1) {
			return nums.size();
		}
		else if(ansLow == -1) {
			return ansHigh;
		}
		else if(ansHigh == -1) {
			return nums.size() - (ansLow + 1);
		}
		return (ansHigh - ansLow - 1);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		ArrayList<ArrayList<Integer>> nums = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			nums.add(new ArrayList<Integer>());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int k = Integer.parseInt(st.nextToken());
			for(int j = 0; j < k; j++) {
				nums.get(i).add(Integer.parseInt(st.nextToken()));
			}
			nums.get(i).sort((a, b) -> a - b);
		}
		for(ArrayList<Integer> i : nums) {
			//System.out.println(i);
		}
		int ans = 0;
		for(int i = n; i < n * 2; i++) {
			//System.out.println("section number " + (i - n));
			for(int j = 0; j < nums.get(i % n).size() - 1; j++) {
				
				int a = nums.get(i % n).get(j);
				int b = nums.get(i % n).get(j + 1);
				int prev = binarySearch(a, b, nums.get((i - 1) % n));
				int next = binarySearch(a, b, nums.get((i + 1) % n));
				//System.out.print(a + " " + b + " : ");
				//System.out.println(prev + " " +  next);
				if(prev != next) {
					ans ++;
				}
			}
		}
		System.out.println(ans);
	}
}
