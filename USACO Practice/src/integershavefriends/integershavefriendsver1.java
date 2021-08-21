package integershavefriends;

import java.util.*;
import java.io.*;

public class integershavefriendsver1 {
	public static void main(String[] args) throws IOException {
		
		//1549D
		
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
			int[] divisors = new int[n];
			int pointer = 0;
			for(int i = 1; i < n; i++) {
				int next = nums[i];
				int nextDivisor = Math.abs(nums[i] - nums[i - 1]);
				divisors[i - 1] = nextDivisor;
				if(i != 1) {
					if(divisors[i - 1] < divisors[i - 2]) {
						if(divisors[i - 2] % divisors[i - 1] != 0) {
							pointer = i - 1;
						}
					}
					else if(divisors[i - 1] > divisors[i - 2]) {
						if(divisors[i - 2] % divisors[i - 1] == 0) {
							divisors[i - 1] = divisors[i - 2];
						}
						else {
							pointer = i - 1;
						}
					}
				}
				while(Math.max(divisors[pointer], nextDivisor) % Math.min(divisors[pointer], nextDivisor) != 0) {
					pointer ++;
				}
				ans = Math.max(ans, i - pointer + 1);
				System.out.print(divisors[i - 1] + " " );
			}
			System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
