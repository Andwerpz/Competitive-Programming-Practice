//package paintingpebbles;

import java.util.*;
import java.io.*;

public class paintingpebbles {
	public static void main(String[] args) throws IOException {
		
		//first, we simplify the problem. If all the pile sizes are above or equal to a certain number; x, for each pile, we can just have x pebbles colored color 1. We only consider sizes above x
		//Now we have a set of piles ranging in size from 0 to lots. Since the minimum size is 0, we can never have more than 1 pebble of the same color in one pile.
		//since the difference would be 2, violating our rule. This means each pile can only have 1 of each color. If any pile has more pebbles than the number of colors, 
		//then the set of piles is invalid. Otherwise, it's pretty easy to figure out which pebble is colored which color. You just go through the size of the pile
		//and count upwards for the color.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		StringBuilder fout = new StringBuilder();
		int base = Integer.MAX_VALUE;
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			base = Math.min(nums[i], base);
		}
		for(int i = 0; i < n; i++) {
			if(nums[i] - base > k) {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			fout.append("YES\n");
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < nums[i]; j++) {
					if(j < base) {
						fout.append("1 ");
					}
					else {
						fout.append(j - base + 1).append(" ");
					}
				}
				fout.append("\n");
			}
		}
		else {
			fout.append("NO\n");
		}
		System.out.print(fout);
	}
}
