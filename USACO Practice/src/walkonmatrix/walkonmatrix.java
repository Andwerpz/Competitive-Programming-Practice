//package walkonmatrix;

import java.util.*;
import java.io.*;

public class walkonmatrix {
	public static void main(String[] args) throws IOException {
		
		//1332D
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int k = Integer.parseInt(fin.readLine());
		int pow = (int) (Math.pow(2, Math.ceil(Math.log(k) / Math.log(2))));
		if(k - pow >= 0) {
			pow *= 2;
		}
		StringBuilder fout = new StringBuilder();
		int[][] ans = new int[3][4];
		ans[0] = new int[] {k + pow, k, k, 0};
		ans[1] = new int[] {pow, 0, k, 0};
		ans[2] = new int[] {pow, pow, k + pow, k};
		fout.append("3 4\n");
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 4; j++) {
				fout.append(ans[i][j]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
