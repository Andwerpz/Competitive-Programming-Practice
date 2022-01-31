//package monstersandspells;

import java.util.*;
import java.io.*;

public class monstersandspells {
	public static void main(String[] args) throws IOException {
		
		//1626C
		
		//you just have to determine which monsters you need to continuously cast the spells to kill. 
		
		//do it greedily starting from the last monster
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long[][] nums = new long[n][2];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][0] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][1] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> Long.compare(a[0], b[0]));
			//go from back to front
			long ans = 0;
			long length = 0;
			int pointer = n - 1;
			while(true) {
				long height = nums[pointer][1];
				long timeDiff = 0;
				while(true) {
					pointer --;
					if(pointer == -1) {
						break;
					}
					long nextHeight = nums[pointer][1];
					timeDiff += nums[pointer + 1][0] - nums[pointer][0];
					long heightAtNext = height - timeDiff;
					if(heightAtNext <= 0) {
						break;
					}
					else {
						height += (nextHeight - heightAtNext) > 0? nextHeight - heightAtNext : 0;
						//System.out.println(height);
					}
				}
				ans += (height * (height + 1)) / 2;
				//System.out.println("FINAL: " + height);
				//System.out.println("POINTER: " + pointer);
				if(pointer == -1) {
					break;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
