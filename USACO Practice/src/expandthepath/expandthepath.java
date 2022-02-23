//package expandthepath;

import java.util.*;
import java.io.*;

public class expandthepath {
	public static void main(String[] args) throws IOException {
		
		//1644E
		
		//notice that if a set of moves doesn't contain both 'R' and 'D', then the answer is always n. 
		
		//if it contains both 'R' and 'D', then notice that you can move all the cells after the first set of 'RD' or 'DR' like a brush
		
		//let h = number of cells before the first 'RD' or 'DR'. 
		
		//the brush is confined to an area of size n * (n - h). Also notice that when you are moving the brush around, you'll lose out on some
		//cells in the top right corner, and bottom left corner. 
		
		//so ans = n * (n - h) - (brushHeight * brushWidth) + (brushHeight + brushWidth - 1) + h
		//                       area of brush                number of cells in brush
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			boolean noBrush = true;
			long hSize = 0;
			char first = s[0];
			for(int i = 0; i < s.length; i++) {
				if(s[i] != first) {
					noBrush = false;
					break;
				}
				hSize ++;
			}
			if(noBrush) {
				fout.append(n).append("\n");
				continue;
			}
			long bWidth = 1;
			long bHeight = 1;
			for(int i = (int) hSize; i < s.length; i++) {
				if(s[i] == 'D') {
					bHeight ++;
				}
				else {
					bWidth ++;
				}
			}
			long mArea = n * (n - hSize);
			long ans = mArea - (bWidth * bHeight) + (bWidth + bHeight - 1) + hSize;
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
