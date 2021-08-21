//package subsequencepermutation;

import java.util.*;
import java.io.*;

public class subsequencepermutation {
	public static void main(String[] args) throws IOException {
		
		//1552A
		
		//compare the sorted sequence with the unsorted sequence. Choose all positions that are different between the two.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] sorted = fin.readLine().toCharArray();
			char[] unsorted = String.valueOf(sorted).toCharArray();
			Arrays.sort(sorted);
			int ans = 0;
			for(int i = 0; i < sorted.length; i++) {
				if(sorted[i] != unsorted[i]) {
					ans ++;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
