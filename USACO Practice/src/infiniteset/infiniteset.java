//package infiniteset;

import java.util.*;
import java.io.*;

public class infiniteset {
	public static void main(String[] args) throws IOException {
		
		//1635D
		
		//think of the array as the starting point of the set, constructing the rest of the set from those.
		
		//give a starting number, x. You can think of all the numbers you can get from applying 2x + 1 and 4x
		//as a sort of tree. There are no duplicate numbers in the tree.
		
		//to prove, notice that the operation 2x + 1 will do a leftwards bitshift and add one, and 4x will do 
		//2 left bitshifts. Notice that the prefix of x is never affected. Thus, if you start from x, you can never
		//get the same number by applying two different sequences of 2x + 1 and 4x. 
		
		//If there are no duplicates in the tree, then it means that there are no duplicates in the two subtrees
		//of 2x + 1 and 4x. This means that if a number can't be made from another number using the operations,
		//then the two numbers will generate completely unique trees. 
		
		//so now we need to determine what numbers are in their own trees, and what numbers are subtrees from
		//other numbers.
		
		//to do this in linear time, we can just put everything into a hashset. To check, start by dividing the number 
		//by 2 if x % 2 == 1, or dividing it by 4 if x % 4 == 0. This will serve to remove any potential operation applied
		//onto it. If it is only divisible by 2, then there is no operation we can remove, and it is a root.
	
		//If at any point, the number is contained within the set, then this number is a subtree.
		
		//Now to get the amount of combinations of operations you can perform, you can do a dp solution. dp[i] will represent
		//the number of different combinations of i bits long. dp[i] = dp[i - 1] + dp[i - 2].
		
		//since we want to take the sum of numbers from dp[0] to dp[p - 1 - len], we can just make a pfx array to make
		//the operation O(1)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int p = Integer.parseInt(st.nextToken()) + 1;
		int mod = (int) (1e9 + 7);
		int[] dp = new int[p];
		dp[0] = 1;
		for(int i = 0; i < p; i++) {
			if(i + 1 < p) {
				dp[i + 1] += dp[i];
				dp[i + 1] %= mod;
			}
			if(i + 2 < p) {
				dp[i + 2] += dp[i];
				dp[i + 2] %= mod;
			}
		}
		for(int i = 1; i < p; i++) {
			dp[i] += dp[i - 1];
			dp[i] %= mod;
			//System.out.println(dp[i]);
		}
		int[] nums = new int[n];
		HashSet<Integer> v = new HashSet<Integer>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			v.add(nums[i]);
		}
		ArrayList<Integer> valid = new ArrayList<Integer>();
		for(int i = 0; i < n; i++) {
			int next = nums[i]; 
			while(true) {
				if(next % 2 == 1) {
					next /= 2;
				}
				else if(next % 4 == 0) {
					next /= 4;
				}
				else {
					valid.add(nums[i]);
					break;
				}
				if(v.contains(next)) {
					break;
				}
				if(next == 0) {
					valid.add(nums[i]);
					break;
				}
			}
		}
		//System.out.println(valid);
		int ans = 0;
		for(int i : valid) {
			int length = Integer.toBinaryString(i).length();
			//System.out.println(i + " " + length);
			if(p - 1 - length >= 0) {
				ans += dp[p - 1 - length];
				ans %= mod;
			}
		}
		System.out.println(ans);
	}
}
