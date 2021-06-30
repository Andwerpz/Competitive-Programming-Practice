//package glider;

import java.util.*;
import java.io.*;

public class glider {
	public static void main(String[] args) throws IOException {
		
		//1041D
		
		//we are trying to maximize the distance that the glider spends in the air. As a base, we can consider the case where the glider doesn't have any rising air segments. Their
		//distance will be equal to their starting height. Now, if we include rising air segments, the maximum sum of distances that the glider can go between air segments is going to
		//be equal to their staring height - 1. subtract 1 since if we hit the ground, then we can't move anymore. Notice that in order to make maximum usage of rising air, the glider must
		//start at the beginning of a rising air segment. This is to minimize the gaps, maximizing the distance. Now, just use two pointer technique, and iterate through the starting points.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int h = Integer.parseInt(st.nextToken());
		int[][] segments = new int[n][2];	//segments don't intersect, and are strictly increasing 
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			segments[i] = new int[] {a, b};
		}
		int pointer = 0;
		int ans = 0;
		int gapSum = 0;
		for(int i = 0; pointer < n; i++) {
			if(i != 0) {
				//System.out.println(pointer);
				gapSum -= segments[i][0] - segments[i - 1][1];
			}
			while(pointer + 1 < n && gapSum + (segments[pointer + 1][0] - segments[pointer][1]) <= h - 1) {
				gapSum += segments[pointer + 1][0] - segments[pointer][1];
				pointer ++;
			}
			int curDist = segments[pointer][1] - segments[i][0] + (h - gapSum);
			ans = Math.max(curDist, ans);
			if(pointer == n - 1) {
				break;
			}
			
		}
		System.out.println(ans);
	}
}
