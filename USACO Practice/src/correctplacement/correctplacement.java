//package correctplacement;

import java.util.*;
import java.io.*;

public class correctplacement {
	public static void main(String[] args) throws IOException {
		
		//1472E
		
		//the bandaid is strong with this one
		//tree based structures are well attuned to the cheese
		
		//solution is pretty slow, can try to implement better, but the idea is there
		
		//you have to construct two pfx arrays, one for width and one for height. Lets look at height. For any given height, what is the minimum width for all people equal to or below this height.
		//this is useful since when at the end when querying people, we can take the height, and easily find the minimum width for all people below this height. If the minimum width is less than
		//the current persons width, then we can put that person in front. Also, when constructing the height, you have to rotate the people, so in the end, you need to consider 2n people. 
		//repeat for width, since what if someone is very wide, but not so tall. Remember, in the height pfx, we track minimum width, so very wide people are left out. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] nums = new int[n][3];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				nums[i][0] = Integer.parseInt(st.nextToken());
				nums[i][1] = Integer.parseInt(st.nextToken());
				nums[i][2] = i;
			}
			Arrays.sort(nums, (a, b) -> a[0] - b[0]);	//sort by height
			TreeMap<Integer, int[]> pfxHeight = new TreeMap<Integer, int[]>();	//for a given height, what is the minimum width that can be found using this height and below
			TreeMap<Integer, int[]> pfxWidth = new TreeMap<Integer, int[]>();	//for a given width, what is the minimum height that can be found using this width and below
			for(int i = 0; i < n; i++) {
				int nextHeight = nums[i][0];
				int nextWidth = nums[i][1];
				int nextId = nums[i][2];
				if(pfxHeight.containsKey(nextHeight)) {
					if(pfxHeight.get(nextHeight)[0] > nextWidth) {
						pfxHeight.put(nextHeight, new int[] {nextWidth, nextId});
					}
				}
				else {
					if(pfxHeight.floorKey(nextHeight) == null) {
						pfxHeight.put(nextHeight, new int[] {nextWidth, nextId});
					}
					else {
						int prevWidth = pfxHeight.floorEntry(nextHeight).getValue()[0];
						int prevId = pfxHeight.floorEntry(nextHeight).getValue()[1];
						pfxHeight.put(nextHeight, new int[] {Math.min(nextWidth, prevWidth), nextWidth < prevWidth? nextId : prevId});
					}
				}
				nextHeight = nums[i][1];
				nextWidth = nums[i][0];
				nextId = nums[i][2];
				if(pfxWidth.containsKey(nextWidth)) {
					if(pfxWidth.get(nextWidth)[0] > nextHeight) {
						pfxWidth.put(nextWidth, new int[] {nextHeight, nextId});
					}
				}
				else {
					if(pfxWidth.floorKey(nextWidth) == null) {
						pfxWidth.put(nextWidth, new int[] {nextHeight, nextId});
					}
					else {
						int prevHeight = pfxWidth.floorEntry(nextWidth).getValue()[0];
						int prevId = pfxWidth.floorEntry(nextWidth).getValue()[1];
						pfxWidth.put(nextWidth, new int[] {Math.min(nextHeight, prevHeight), nextHeight < prevHeight? nextId : prevId});
					}
				}
			}
			
			
			
			
			
				
			Arrays.sort(nums, (a, b) -> a[1] - b[1]);
			for(int i = 0; i < n; i++) {
				int nextHeight = nums[i][0];
				int nextWidth = nums[i][1];
				int nextId = nums[i][2];
				if(pfxWidth.containsKey(nextWidth)) {
					if(pfxWidth.get(nextWidth)[0] > nextHeight) {
						pfxWidth.put(nextWidth, new int[] {nextHeight, nextId});
					}
				}
				else {
					if(pfxWidth.floorKey(nextWidth) == null) {
						pfxWidth.put(nextWidth, new int[] {nextHeight, nextId});
					}
					else {
						int prevHeight = pfxWidth.floorEntry(nextWidth).getValue()[0];
						int prevId = pfxWidth.floorEntry(nextWidth).getValue()[1];
						pfxWidth.put(nextWidth, new int[] {Math.min(nextHeight, prevHeight), nextHeight < prevHeight? nextId : prevId});
					}
				}
				nextHeight = nums[i][1];
				nextWidth = nums[i][0];
				nextId = nums[i][2];
				if(pfxHeight.containsKey(nextHeight)) {
					if(pfxHeight.get(nextHeight)[0] > nextWidth) {
						pfxHeight.put(nextHeight, new int[] {nextWidth, nextId});
					}
				}
				else {
					if(pfxHeight.floorKey(nextHeight) == null) {
						pfxHeight.put(nextHeight, new int[] {nextWidth, nextId});
					}
					else {
						int prevWidth = pfxHeight.floorEntry(nextHeight).getValue()[0];
						int prevId = pfxHeight.floorEntry(nextHeight).getValue()[1];
						pfxHeight.put(nextHeight, new int[] {Math.min(nextWidth, prevWidth), nextWidth < prevWidth? nextId : prevId});
					}
				}
			}
			int[] ans = new int[n];
			for(int i = 0; i < n; i++) {
				int[] next = nums[i];
				int id = next[2];
				int minWidth = Integer.MAX_VALUE;
				int minHeight = Integer.MAX_VALUE;
				if(pfxHeight.floorEntry(next[0] - 1) != null) {
					minWidth = pfxHeight.floorEntry(next[0] - 1).getValue()[0];
				}
				if(pfxWidth.floorEntry(next[1] - 1) != null) {
					minHeight = pfxWidth.floorEntry(next[1] - 1).getValue()[0];
				}
				if(minWidth < next[1]) {
					ans[id] = pfxHeight.floorEntry(next[0] - 1).getValue()[1] + 1;
				}
				else if(minHeight < next[0]) {
					ans[id] = pfxWidth.floorEntry(next[1] - 1).getValue()[1] + 1;
				}
				else {
					ans[id] = -1;
				}
			}
			for(int i = 0; i < n; i++) {
				fout.append(ans[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
