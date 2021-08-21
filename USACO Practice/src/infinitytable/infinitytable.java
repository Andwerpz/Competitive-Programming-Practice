//package infinitytable;

import java.util.*;
import java.io.*;

public class infinitytable {
	public static void main(String[] args) throws IOException {
		
		//1560C
		
		//what i did is binary search for which layer the number is located, and then getting the exact coordinates is trivial.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long[] pfx = new long[100000];
		long increment = 1;
		for(int i = 0; i < pfx.length; i++) {
			pfx[i] += increment;
			if(i != 0) {
				pfx[i] += pfx[i - 1];
			}
			//System.out.println(pfx[i]);
			increment += 2;
		}
		while(t-- > 0) {
			long k = Integer.parseInt(fin.readLine());
			int pointer = pfx.length - 1;;
			int high = pfx.length - 1;
			int low = 0;
			int mid = low + (high - low) / 2;
			while(low <= high) {
				if(pfx[mid] >= k) {
					pointer = Math.min(pointer, mid);
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			//System.out.println(pfx[pointer] + " " + pointer);
			long diff = 1;
			increment = 1;
			if(pointer != 0) {
				increment = pfx[pointer] - pfx[pointer - 1];
				diff = k - pfx[pointer - 1];
			}
			int r = 1;
			int c = pointer + 1;
			if(diff <= increment / 2 + 1) {
				r = (int) diff;
			}
			else {
				r = (int) (increment / 2 + 1);
				c -= (int) (diff - (increment / 2 + 1));
			}
			fout.append(r).append(" ").append(c).append("\n");
		}
		System.out.print(fout);
	}
}
