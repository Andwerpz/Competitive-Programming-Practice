//package easternexhibition;

import java.util.*;
import java.io.*;

public class easternexhibition {
	public static void main(String[] args) throws IOException {
		
		//1486B
		
		//all you have to do is find the rectangle marked out by the median x and y coordinates of points. The 
		//area of the rectangle is the number of possible locations that you can put the exhibition. Note that if n is odd, then 
		//the median for both x and y is the same number, and the amount of locations is always 1.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] x = new int[n];
			int[] y = new int[n];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				x[i] = Integer.parseInt(st.nextToken());
				y[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(x);
			Arrays.sort(y);
			if(n % 2 == 1) {
				fout.append("1\n");
			}
			else {
				long xLow = x[n / 2 - 1];
				long xHigh = x[n / 2] + 1;
				long yLow = y[n / 2 - 1];
				long yHigh = y[n / 2] + 1;
				//System.out.println((xHigh - xLow) + " " + (yHigh - yLow));
				fout.append((xHigh - xLow) * (yHigh - yLow)).append("\n");
			}
		}
		System.out.print(fout);
	}
}
