//package carryingconundrum;

import java.util.*;
import java.io.*;

public class carryingconundrum {
	public static void main(String[] args) throws IOException {
		
		//1567C
		
		//huh, i should have solved this. Would have gotten me so many more points.
		
		//notice that since you only carry between every other one, you can split the problem into two different addition problems. 
		
		//just calculate the amount of combos that you can achieve between the two split problems. One thing to note is that both the bottom and top number must be greater than 0 at all times.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int a = 0;
			int b = 0;
			int power = 1;
			for(int i = s.length - 1; i >= 0; i -= 2) {
				a += Integer.parseInt(s[i] + "") * power;
				power *= 10;
			}
			power = 1;
			for(int i = s.length - 2; i >= 0; i -= 2) {
				b += Integer.parseInt(s[i] + "") * power;
				power *= 10;
			}
			//System.out.println(a + " " + b);
			int ans = 0;
			if(a == 0) {
				ans = b - 1;
			}
			else if(b == 0) {
				ans = a - 1;
			}
			else {
				if(a >= 2 && b >= 2) {
					ans += (a - 1) * (b - 1);
				}
				if(a >= 1) {
					ans += (b - 1) * 2;
				}
				if(b >= 1) {
					ans += (a - 1) * 2;
				}
				ans += 2;
			}
			
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
