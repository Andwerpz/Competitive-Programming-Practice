//package kamazingnumbers;

import java.util.*;
import java.io.*;

public class kamazingnumbers {
	public static void main(String[] args) throws IOException {
		
		//1416A
		
		//huh, that's pretty smart. check tutorial
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] maxGap = new int[n][2];
			int[] lastPos = new int[n];
			for(int i = 0; i < n; i++) {
				maxGap[i][0] = -1;
				maxGap[i][1] = i + 1;
			}
			Arrays.fill(lastPos, -1);
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken()) - 1;
				if(maxGap[next][0] == 0) {
					maxGap[next][0] = i + 1;
				}
				else {
					int prev = lastPos[next];
					maxGap[next][0] = Math.max(maxGap[next][0], i - prev);
				}
				lastPos[next] = i;
			}
			for(int i = 0; i < n; i++) {
				if(lastPos[i] != -1) {
					maxGap[i][0] = Math.max(maxGap[i][0], n - lastPos[i]);
				}
			}
			Arrays.sort(maxGap, (a, b) -> a[0] == b[0]? a[1] - b[1] : a[0] - b[0]);
			int pointer = -1;
			while(maxGap[pointer + 1][0] == -1) {
				pointer ++;
			}
			int min = -1;
			int[] ans = new int[n];
			for(int i = 0; i < n; i++) {
				while(pointer + 1 < n && maxGap[pointer + 1][0] <= i + 1) {
					pointer ++;
					if(min == -1) {
						min = maxGap[pointer][1];
					}
					else {
						min = Math.min(min, maxGap[pointer][1]);
					}
				}
				ans[i] = min;
			}
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
