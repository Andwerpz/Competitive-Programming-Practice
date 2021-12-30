//package singerstour;

import java.util.*;
import java.io.*;

public class singerstour {
	public static void main(String[] args) throws IOException {
		
		//1618E
		
		//notice that if you add a minute to the a array, then the total sum of minutes performed will increase by n * (n + 1) / 2. 
		//you can use this to find out the total sum of the a array, by getting the sum of the b array, and dividing it by n * (n + 1) / 2.
		//you can also use this to rule out any b array which isn't divisible. 
		
		//now that you have the total expected sum of the a array, time to construct it. First, notice that when you walk along the b array,
		//you would expect for each subsequent value to increase by exactly amt. But this isn't always the case. Notice that when
		//the values increase by less than amt, the difference between the increase and amt has to be divisible by n. This represents 
		//where the values of a are located, as a singer has completed their cycle. 
		
		//to solve, just walk along the b array, and calculate each a value according to the discrepancies in differences in the b array.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long[] nums = new long[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long unit = (n * (n + 1)) / 2;
			long sum = 0;
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				sum += nums[i];
				if(nums[i] < unit) {
					isValid = false;
				}
			}
			if(sum % unit != 0 || !isValid) {
				fout.append("NO\n");
				continue;
			}
			
			long amt = sum / unit;
			long[] ans = new long[n];
			sum = 0;
			//System.out.println("AMT: " + amt);
			for(int i = 1; i <= n; i++) {	//expected increase is amt. (amt - actual diff) / n = a[i]
				long diff = nums[i % n] - nums[i - 1];
				//System.out.println(diff);
				ans[i % n] = (amt - diff) / n;
				if(ans[i % n] < 0) {
					isValid = false;
				}
				sum += ans[i % n];
			}
			//System.out.println("SUM: " + sum);
			if(!isValid || sum != amt) {
				fout.append("NO\n");
				continue;
			}
			fout.append("YES\n");
			for(long l : ans) {
				fout.append(l).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
