//package polygonfortheangle;

import java.util.*;
import java.io.*;

public class polygonfortheangle {
	
	public static boolean isWhole(double val) {
		return 0 == val - Math.floor(val);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1096C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int a = Integer.parseInt(fin.readLine());
			boolean isValid = false;
			for(int i = 3; i <= 360; i++) {
				double totAngle = (i - 2) * 180;
				double intAngle = totAngle / i;
				double divAngle = intAngle / (i - 2);
				for(int j = 1; j <= (i - 2); j++) {
					if(isWhole(divAngle * ((double)(j))) && a == (int) (divAngle * ((double) j))) {
						isValid = true;
						fout.append(i).append("\n");
						break;
					}
				}
				if(isValid) {
					break;
				}
			}
			if(!isValid) {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
