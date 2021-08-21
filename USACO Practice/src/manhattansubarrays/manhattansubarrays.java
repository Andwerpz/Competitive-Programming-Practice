//package manhattansubarrays;

import java.util.*;
import java.io.*;

public class manhattansubarrays {
	public static void main(String[] args) throws IOException {
		
		//1550C
		
		//notice that the maximum valid subarray length is always going to be 4. This means for each number, you can just check how many valid subarrays there are from 1 - 4 starting from
		//that number.
		
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
			long ans = 0;
			int pointer = 0;
			for(int i = 0; i < n; i++) {
				boolean leftBound = false;
				boolean rightBound = false;
				int left = 0;
				int right = 0;
				int numLeft = 0;
				int numRight = 0;
				int cur = nums[i];
				pointer = 0;
				while(pointer + i + 1 < n) {
					pointer ++;
					int next = nums[i + pointer];
					if(next == cur) {
						if(numLeft <= 1 && numRight <= 1 && left != next && right != next) {
							left = next;
							right = next;
							leftBound = true;
							rightBound = true;
							numLeft ++;
							numRight ++;
						}
						else {
							pointer --;
							break;
						}
					}
					else if(next < cur) {
						if(!leftBound && numRight != 2) {
							leftBound = true;
							left = next;
							numLeft ++;
						}
						else if(next <= left || numLeft >= 2 || numRight >= 2){
							pointer --;
							break;
						}
						else {
							left = next;
							numLeft ++;
						}
					}
					else if(next > cur) {
						if(!rightBound && numLeft != 2) {
							rightBound = true;
							right = next;
							numRight ++;
						}
						else if(next >= right || numRight >= 2 || numLeft >= 2) {
							pointer --;
							break;
						}
						else {
							right = next;
							numRight ++;
						}
					}
					
				}
				//System.out.println(left + " " + right + " " + pointer);
				ans += pointer + 1;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
