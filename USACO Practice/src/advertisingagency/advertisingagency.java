//package advertisingagency;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class advertisingagency {
	
	static int mod = 1000000007;
	
	public static BigInteger factorial(long val) {
		BigInteger ans = new BigInteger("1");
		for(long i = 1; i <= val; i++) {
			ans = ans.multiply(new BigInteger(i + ""));
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1475E
		
		//big integer so good, save everything in big integer.
		
		//to get the maximum amount of followers, you just need to buy the k highest bloggers.
		//now, you need to find the amount of combinations that will get you the highest amount of followers, with k bloggers. To do this, the only way you can is
		//by buying different combinations of bloggers with the same amount of followers. If you buy a new blogger with more or less followers, you can either get more followers than
		//your "maximum" or you're buying under your maximum. So the simple solution is to just calculate the number of combinations that you can buy the bloggers of the lowest follower count
		//in your maximum. Any blogger with a higher amount of followers have already been bought, so you can't make any new combinations with them.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			int end = 0;
			int choose = 0;
			for(int i = n - 1; i >= 0; i--) {
				if(end != nums[i]) {
					end = nums[i];
					choose = 1;
				}
				else {
					choose ++;
				}
				k--;
				if(k == 0) {
					break;
				}
			}
			int quantity = 0;
			for(int i = 0; i < n; i++) {
				if(nums[i] == end) {
					quantity ++;
				}
			}
			//System.out.println(quantity + " " + choose);
			BigInteger ans = factorial(quantity).divide(factorial(choose).multiply(factorial(quantity - choose)));
			ans = ans.mod(new BigInteger(mod + ""));
			fout.append(ans.toString()).append("\n");
		}
		System.out.print(fout);
	}
}
