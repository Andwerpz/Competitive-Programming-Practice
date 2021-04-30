//package kyoyaandcoloredballs;

import java.util.*;
import java.io.*;

public class kyoyaandcoloredballs {
	public static void main(String[] args) throws IOException {
		
		//so the one twist to this problem is that we have to "finish" pulling all the balls of one color in a certain order.
		//we finish pulling ball color 1, then 2, then 3. you can pull a 3 before you ever pull a 1, but you must pull the last 1 before you pull the last 2
		//and last 2 before last 3. 
		//what we do is count permutations. We start by putting all the 1s in a line. Then, when we consider 2s, put one 2 at the end of the line. this guarantees that the last 1
		//is pulled before the last 2, and that the last 2 is after the last 1. Then count all the permutations of the remaining 1s and 2s. Next, consider color 3. Do the same thing
		//and put one color 3 ball at the end, guaranteeing its position, and calculate all the permutations of the color 3 balls with the rest of the balls. Multiply this number by the previous number
		//and repeat until you run out of colors.
		//when counting permutations, you only have to consider the changing position of the new color. Since you already calculated all valid positions of the previous color in 
		//the previous dp state, all you have to do is worry about what positions you can place the new balls in, and multiply that number by the number of valid permutations
		//in the previous state, and then you have the number of valid permutations for this state.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(fin.readLine());
		}
		long mod = 1000000007;
		long ans = 1;
		int curBalls = 0;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			if(next != 1 && i != 0) {
				long[][] pfx = new long[next  - 1][curBalls + 1];
				for(int j = 0; j <= curBalls; j++) {
					pfx[0][j] = curBalls - j + 1;
					////System.out.print(pfx[0][j] + " ");
				}
				////System.out.println();
				for(int j = 1; j < next - 1; j++) {
					for(int k = curBalls; k >= 0; k --) {
						if(k == curBalls) {
							pfx[j][k] = pfx[j - 1][k];
						}
						else {
							pfx[j][k] = pfx[j - 1][k] + pfx[j][k + 1];
							pfx[j][k] %= mod;
						}
						////System.out.print(pfx[j][k] + " ");
					}
					////System.out.println();
				}
//				for(long[] j : pfx) {
//					for(long k : j) {
//						//System.out.print(k + " ");
//					}
//					//System.out.println();
//				}
				if(next > 1) {
					
					ans *= pfx[next - 2][0];
					ans %= mod;
					//System.out.println("add");
				}
			}
			
			
			ans %= mod;
			curBalls += next;
			//System.out.println("CUR BALLS: " + curBalls);
			//System.out.println("ANS: " + ans);
		}
		System.out.println(ans);
	}
}
