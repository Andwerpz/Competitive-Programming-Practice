//package mexandarray;

import java.util.*;
import java.io.*;

public class mexandarray {
	public static void main(String[] args) throws IOException {
		
		//1637B
		
		//notice that you get a point for the number of segments, and the sum of mex over all segments. 
		//if you were to have a segment [0, 1], with a mex of 2, your total score would be 3, as opposed to having 2 segments [0], [1]
		//with the same score 3. 
		
		//notice that if you make the segment mex bigger, then you're sacrificing a score from the extra segment
		
		//so just make each number it's own segment
		
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
			int ans = 0;
			for(int i = 0; i < n; i++) {
				for(int j = i; j < n; j++) {
					for(int k = i; k <= j; k++) {
						ans += nums[k] == 0? 2 : 1;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
