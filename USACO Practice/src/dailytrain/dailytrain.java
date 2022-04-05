//package dailytrain;

import java.util.*;
import java.io.*;

public class dailytrain {
	public static int factorial(int x) {
		if(x == 0) {
			return 0;
		}
		int ans = 1;
		for(int i = 2; i <= x; i++) {
			ans *= i;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//CodeChef DAILY
		
		//get the sums of empty seats for each compartment
		
		//this is a simple combo problem of x choose y. 
		
		//x! / ((x - y)! * y!)
		
		//we want to get the number of different combinations from x of size y.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int ans = 0;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int x = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		while(n-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int[] car = new int[9];
			for(int i = 0; i < 36; i++) {
				car[i / 4] += s[i] == '0'? 1 : 0;
			}
			for(int i = 36; i < 54; i++) {
				car[8 - ((i - 36) / 2)] += s[i] == '0'? 1 : 0;
			}
			for(int i = 0; i < 9; i++) {
				//System.out.println(car[i]);
				if(x <= car[i]) {
					int add = 1;
					for(int j = car[i]; j > car[i] - x; j--) {
						add *= j;
					}
					add /= factorial(x);
					ans += add;
					//System.out.println(add);
				}
			}
		}
		System.out.println(ans);
	}
}
