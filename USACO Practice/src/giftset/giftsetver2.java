package giftset;

import java.util.*;
import java.io.*;

public class giftsetver2 {
	public static void main(String[] args) throws IOException {
		
		//1538G
		
				//i keep getting these weird wrong answers. Check tutorial for better explanation
				
				//basically, we can represent the situation using a set of linear equations. Lets say that you want to make n sets. Define the first type of set using a red candies and b blue candies, and 
				//the second type using b red candies and a blue candies. Given that you want to make k of the first set, you can define the following inequalities:
				
				//x >= a * k + b * (n - k);
				//y >= b * k + a * (n - k);
				
				//to see if any n is a good value, you just have to solve for k, and see if there is a solution that is a positive integer.
				
				//you can binary search through the range.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long x = Integer.parseInt(st.nextToken());
			long y = Integer.parseInt(st.nextToken());
			long a = Integer.parseInt(st.nextToken());
			long b = Integer.parseInt(st.nextToken());
			long ans = 0;
			if(a == b) {
				ans = Math.min(x / a, y / a);
			}
			else {
				if(a < b) {
					long temp = a;
					a = b;
					b = temp;
				}
				long low = 0;
				long high = (int) (1e9 + 100);
				long mid = low + (high - low) / 2;
				while(high - low > 1) {
					mid = (low + high) / 2;
					long right = (long) Math.floor((x - mid * b) * 1.0 / (double) (a - b));
					long left = (long) Math.ceil((y - mid * a) * 1.0 / (double) (b - a));
					if(Math.max(left, 0l) <= Math.min(right, mid)) {
						low = mid;
					}
					else {
						high = mid;
					}
				}
				ans = low;
			}
			
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
