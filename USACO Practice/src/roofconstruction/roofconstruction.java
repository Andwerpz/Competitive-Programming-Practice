package roofconstruction;

import java.util.*;
import java.io.*;

public class roofconstruction {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[(int) Math.pow(2, 1 + (int) (Math.log(n) / Math.log(2)))];
			int pow = 1;
			for(int i = 0; i < 14; i++) {
				pow = (int) Math.pow(2, i);
				int cycle = pow * 4;
				for(int j = 0; j < nums.length; j++) {
					int count = (j % cycle) + 1;
					if(!(count <= (cycle / 4) || count > (cycle - (cycle / 4)))) {
						nums[j] += pow;
					}
				}
			}
			for(int i : nums) {
				System.out.println(Integer.toBinaryString(i));
				if(i < n) {
					fout.append(i).append(" ");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
