//package onedsokoban;

import java.util.*;
import java.io.*;

public class onedsokoban {
	
	public static int getNumInRange(int l, int r, Integer[] nums) {	//searching values not indexes
		int pLow = nums.length - 1;
		int pHigh = 0;
		int low = 0;
		int high = nums.length - 1;
		int mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums[mid] >= l) {
				pLow = Math.min(pLow, mid);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		low = 0;
		high = nums.length - 1;
		mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums[mid] <= r) {
				pHigh = Math.max(pHigh, mid);
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return pHigh - pLow + 1;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1494C
		
		//since you can't pull boxes, and you cant go over boxes, you can treat each side of the playfield as a separate problem. The relative order of boxes won't ever change, and
		//negative boxes won't ever become positive boxes, and vice versa. 
		
		//from there, just try all positions as end points. To get the number of positions covered, just do binary search from the end position. The range will be the number of 
		//boxes that you are pushing so far.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			Integer[] boxes = new Integer[n];
			Integer[] positions = new Integer[m];
			int prev = Integer.MIN_VALUE;
			int midBox = -1;
			int midPosition = -1;
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				boxes[i] = Integer.parseInt(st.nextToken());
				if(prev < 0 && 0 < boxes[i]) {
					midBox = i;
				}
				prev = boxes[i];
			}
			prev = Integer.MIN_VALUE;
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				positions[i] = Integer.parseInt(st.nextToken());
				if(prev < 0 && 0 < positions[i]) {
					midPosition = i;
				}
				prev = positions[i];
			}
			if(midBox == -1) {
				midBox = n;
			}
			if(midPosition == -1) {
				midPosition = m - 1;
			}
			int ans = 0;
			int max = 0;
			int posPointer = midPosition;
			int counter = 0;
			//System.out.println("MID BOX: " + midBox + " MID POS: " + midPosition);
			for(int i = midBox; i > 0; i --) {
				counter ++;
				int next = boxes[i - 1];
				while(posPointer != -1 && positions[posPointer] > next) {
					posPointer --;
				}
				if(posPointer == -1) {
					break;
				}
				int nextBox = i == 1? Integer.MIN_VALUE : boxes[i - 2];
				while(posPointer != -1 && positions[posPointer] > nextBox) {
					if(positions[posPointer] == next) {
						max ++;
					}
					max = Math.max(max, getNumInRange(positions[posPointer], Math.min(0, positions[posPointer] + (counter - 1)), positions));
					//System.out.println(positions[posPointer] + (counter - 1));
					posPointer --;
				}
			}
			//System.out.println("FIRST MAX: " + max);
			counter = 0;
			ans += max;
			max = 0;
			posPointer = midPosition;
			for(int i = midBox; i < n; i++) {
				counter ++;
				int next = boxes[i];
				while(posPointer != m && positions[posPointer] < next) {
					posPointer ++;
				}
				if(posPointer == m) {
					break;
				}
				int nextBox = i == n - 1? Integer.MAX_VALUE : boxes[i + 1];
				while(posPointer != m && positions[posPointer] < nextBox) {
					if(positions[posPointer] == next) {
						max ++;
					}
					max = Math.max(max, getNumInRange(Math.max(0, positions[posPointer] - (counter - 1)), positions[posPointer], positions));
					//System.out.println("POS: " + positions[posPointer]);
					//System.out.println(positions[posPointer] - (counter - 1) + " pos");
					posPointer ++;
				}
			}
			//System.out.println("SECOND MAX: " + max);
			ans += max;
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
