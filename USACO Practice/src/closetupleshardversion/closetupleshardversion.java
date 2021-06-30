package closetupleshardversion;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class closetupleshardversion {
	
	static int m;
	static long mod = 1000000007;
	static long[][] factorial;
	
	public static long sum(long val) {
		if(val < m) {
			return 0;
		}
		else if(m - 1 == 0) {
			return 1;
		}
		else if(val - 1 <= 0 || m - 1 <= 0) {
			return 0;
		}
		else if(val - 1 == m - 1) {
			return 1;
		}
		//System.out.println("VAL: " + val + " M: " + (m - 1) + " FACTORIAL: " + factorial[m - 1] + " FACTORIAL2: " + factorial[(int) ((val - 1) - (m - 1))]);
		long ans = factorial[m - 2][(int) (val - 2)];
		System.out.println("ANS: " + ans);
		//System.out.println("ANS: " + ans);
		return ans;
	}
	
	public static void factorial(int m) {
		factorial[m - 1][m - 1] = 1;
		for(int i = m; i < factorial.length; i++) {
			factorial[m - 1][i] = 1;
			for(int j = 0; j < m; j++) {
				factorial[m - 1][i] *= i - j + 1;
				factorial[m - 1][i] %= mod;
			}
			//System.out.print(factorial[m - 1][i] + " ");
		}
		
	}

	
	public static void wrapper() {
		for(int i = 0; i < 100; i++) {
			factorial(i + 1);
		}
		for(long[] i : factorial) {
		for(long j : i) {
				System.out.print(j + " ");
			}
			System.out.println();
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1462E2
		
		//need to be able to precalculate all values for m from 0 - 10 ^ 5 * 2
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		factorial = new long[100][101];
		wrapper();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			for(int i : nums) {
				System.out.print(i + " ");
			}
			System.out.println();
			int pointer = 0;	//points at the last number that is within the range nums[i] - (nums[i] - k)
			long ans = 0;
			System.out.println("M: " + m);
			for(int i = 0; i < n; i++) {
				int next = nums[i];
				while(pointer + 1 < n && next - nums[pointer] > k + 1) {
					pointer ++;
				}
				System.out.println("I: " + i + ", " + nums[i] + " POINTER: " + pointer + ", " + nums[pointer]);
				System.out.println("RANGE: " + (i - pointer + 1));
				ans += sum(i - pointer + 1);
				ans %= mod;
			}
			System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
