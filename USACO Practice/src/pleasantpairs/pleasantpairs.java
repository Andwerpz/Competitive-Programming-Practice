//package pleasantpairs;

import java.util.*;
import java.io.*;

public class pleasantpairs {
	public static void main(String[] args) throws IOException {
		
		//1541B
		
		//sort the numbers in ascending order, and save their indexes. Now, start from the least number, and test it against all the other numbers. When the product goes above
		//n * 2, then stop testing this number, and move on to the next number. This will have around O(n * log(n)) efficiency since every time you go up a number,
		//you're reducing the amount of larger numbers you need to check.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] nums = new int[n][2];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][0] = Integer.parseInt(st.nextToken());
				nums[i][1] = i + 1;
			}
			Arrays.sort(nums, (a, b) -> a[0] - b[0]);
			long ans = 0;
			outer:
			for(int i = 0; i < n; i++) {
				for(int j = i + 1; j < n; j++) {
					long mult = nums[i][0] * nums[j][0];
					long add = nums[i][1] + nums[j][1];
					if(add == mult) {
						ans ++;
					}
					if(mult > 2 * n) {
						if(j - 1 == i) {
							break outer;
						}
						break;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
