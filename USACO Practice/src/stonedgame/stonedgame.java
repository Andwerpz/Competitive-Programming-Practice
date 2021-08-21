//package stonedgame;

import java.util.*;
import java.io.*;

public class stonedgame {
	public static void main(String[] args) throws IOException {
		
		//1396B
		
		//the answer is for each turn, just pick the largest pile.
		
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
			int prev = -1;
			boolean tTurn = true;
			while(true) {
				int max = 0;
				int maxIndex = 0;
				for(int i = 0; i < n; i++) {
					if(nums[i] > max && i != prev) {
						max = nums[i];
						maxIndex = i;
					}
				}
				if(max == 0) {
					fout.append(tTurn? "HL\n" : "T\n");
					break;
				}
				prev = maxIndex;
				nums[maxIndex] --;
				tTurn = !tTurn;
			}
		}
		System.out.print(fout);
	}
}
