//package prettypermutations;

import java.util.*;
import java.io.*;

public class prettypermutations {
	public static void main(String[] args) throws IOException {
		
		//1541A
		
		//if you group the cats into groups of 2, then you can switch each cat, and the cost will be equal to the number of cats. If there is an odd number
		//of cats, make 1 group of 3.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] ans = new int[n];
			for(int i = 0; i < n; i++) {
				ans[i] = i + 1;
				if(i % 2 == 1 && !(i == n - 1 && n % 2 == 1)) {
					int temp = ans[i - 1];
					ans[i - 1] = ans[i];
					ans[i] = temp;
				}
			}
			if(n % 2 == 1) {
				int temp = ans[n - 1];
				ans[n - 1] = ans[n - 2];
				ans[n - 2] = temp;
			}
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
