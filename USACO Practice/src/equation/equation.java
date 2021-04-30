//package equation;

import java.util.*;
import java.io.*;

public class equation {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		double c = Double.parseDouble(fin.readLine());
		double low = 0;
		double high = c;
		double mid = low + (high - low) / 2;
		while(high - low > Math.pow(10, -7)) {
			if(Math.pow(mid, 2) + Math.sqrt(mid) > c) {
				high = mid;
			}
			else {
				low = mid;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(mid);
	}
}
