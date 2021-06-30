//package mixingwater;

import java.util.*;
import java.io.*;

public class mixingwater {
	public static void main(String[] args) throws IOException {
		
		//1359C
		
		//if you use binary search to get the answer, then you'll run into precision problems, since the problem doesn't give any tolerance for error.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int test = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(test-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int h = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int t = Integer.parseInt(st.nextToken());
			if (h + c - 2 * t >= 0)
				fout.append("2\n");
			else{
				int a = h - t;
				int b = 2 * t - c - h;
				int k = 2 * (a / b) + 1;
				long val1 = Math.abs(k / 2 * 1l * c + (k + 1) / 2 * 1l * h - t * 1l * k);
				long val2 = Math.abs((k + 2) / 2 * 1l * c + (k + 3) / 2 * 1l * h - t * 1l * (k + 2));
				fout.append(val1 * (k + 2) <= val2 * k ? k : k + 2).append("\n");
			}
		}
		System.out.print(fout);
	}
}
