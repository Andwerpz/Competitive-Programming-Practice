package countingdivisors;

import java.util.*;
import java.io.*;

public class countingdivisors {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int[] maxDiv = new int[1100001];
		for(int i = 2; i < maxDiv.length; i++) {
			if(maxDiv[i] == 0) {
				for(int j = i; j < maxDiv.length; j += i) {
					maxDiv[j] = i;
				}
			}
		}
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int ans = 1;
			if(n == 1) {
				fout.append("1\n");
				break;
			}
			while(true) {
				int div = maxDiv[n];
				int count = 0;
				while(n % div == 0) {
					n /= div;
					count ++;
				}
				ans *= (count + 1);
				if(n == 1) {
					break;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
