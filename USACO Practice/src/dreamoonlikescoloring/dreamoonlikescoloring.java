//package dreamoonlikescoloring;

import java.util.*;
import java.io.*;

public class dreamoonlikescoloring {
	public static void main(String[] args) throws IOException {
		
		//1329A
		
		//this one took quite a few attempts. The trick is to turn the original problem on its head. Instead of considering the layers of paint in the correct order, consider
		//them in reverse order.
		
		//Put the last layer of paint in the furthest right position you can put it. Then put the next layer of paint in the farthest left position you can have it still touching the previous layer of paint, while
		//also keeping m - 2 units distance from the left wall. Continue this, until you run out of paint. If m > n, then we know that the input will be invalid since you can't have m different colors
		//if the number of cells is less than m. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nums = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			nums[i] = Integer.parseInt(st.nextToken()) - 1;
		}
		if(m > n) {
			System.out.println(-1);
		}
		else {
			int sum = m;
			int[] ans = new int[m];
			int startPointer = n;
			int endPointer = n + 1;
			boolean isValid = true;
			for(int i = m - 1; i >= 0; i--) {
				int next = nums[i];
				
				startPointer = Math.min(startPointer, n - next);
				//System.out.println("FIRST: " + startPointer + " " + next);
				if(startPointer < 1) {
					isValid = false;
					break;
				}
				while(startPointer > i + 1 && startPointer + next >= endPointer) {
					startPointer --;
				}
				ans[i] = startPointer;
				endPointer = startPointer;
				//System.out.println(startPointer);
				startPointer --;
			}
			if(startPointer != 0) {
				isValid = false;
			}
			if(isValid) {
				StringBuilder fout = new StringBuilder();
				for(int i = 0; i < ans.length; i++) {
					fout.append(ans[i]).append(" ");
				}
				System.out.print(fout);
			}
			else {
				System.out.println(-1);
			}
		}
	}
}
