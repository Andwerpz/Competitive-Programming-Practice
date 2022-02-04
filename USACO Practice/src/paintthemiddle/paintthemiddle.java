//package paintthemiddle;

import java.util.*;
import java.io.*;

public class paintthemiddle {
	public static void main(String[] args) throws IOException {
		
		//1631E
		
		//first, notice that given x, y where a[x] = a[y], and x < y, you can apply the operation on index
		//from x - y. 
		
		//it follows that only the first and last occurrences of each number have any significance. We can 
		//view each number as a segment from its first occurrence to its last occurrence. 
		
		//notice that if two segments overlap, and one segment doesn't completely contain the other, the way to
		//do the most operations is to color in the entirety of one segment, except for the endpoint of the other segment.
		//then, we can color in the entirety of the other segment, including the endpoint of the first segment.
		
		//notice that every time you append another segment onto your set of overlapping segments, you lose a potential
		//operation. 
		
		//instead of maximizing operations, perhaps we can try to minimize lost operations. We do this by minimizing the number
		//of segments we perform these operations on. 
		
		//the algorithms is as follows:
		
		//start with the leftmost segment.
		
		//find the number with the rightmost boundary within the segment, only considering uncolored indicies.
		
		//if this maximum boundary is equal to the current rightmost boundary, then color in all the indicies within the segment
		//and find the next leftmost segment
		
		//else, color in everything, except for the new segment's left boundary. 
		
		//repeat until the rightmost boundary = n - 1.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		for(int i = n - 1; i >= 0; i--) {
			if(!dict.keySet().contains(nums[i])) {
				dict.put(nums[i], i);
			}
		}
		int numSeg = 1;
		int l = 0;
		int r = dict.get(nums[0]);
		while(true) {
			int maxR = r;
			for(int i = l + 1; i < r; i++) {
				maxR = Math.max(maxR, dict.get(nums[i]));
			}
			if(maxR == r) {
				if(r != l) {	//there have to be 2 end points
					numSeg ++;	//ending this connected set
				}
				
				if(r == n - 1) {
					break;
				}
				//System.out.println(r + 1);
				numSeg ++;	//starting a new connected set
				l = r + 1;
				r = dict.get(nums[r + 1]);
				continue;
			}
			l = r;
			r = maxR;
			numSeg ++;
		}
		//System.out.println(numSeg);
		System.out.println(n - numSeg);
	}
}
