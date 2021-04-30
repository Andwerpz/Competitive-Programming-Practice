package studentcouncils;

import java.io.*;
import java.util.*;

public class studentcouncils {
	
	static int[] s;
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int k = Integer.parseInt(fin.readLine());
		int n = Integer.parseInt(fin.readLine());
		int sum = 0;
		s = new int[n + 1];	//we make s[0] = 0 so that we have a baseline to compare with
		for(int i = 1; i <=  n; i++) {
			s[i] = Integer.parseInt(fin.readLine());
			sum += s[i];
		}
		int low = 0;
		int high = sum / k + 1;
		int mid = low + (high - low) / 2;
		int ans = low;
	}
}
