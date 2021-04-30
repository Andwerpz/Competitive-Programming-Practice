//package everyoneisawinner;

import java.util.*;
import java.io.*;

public class everyoneisawinner {
	
	public static int search(int l, int val) {
		int low = 1;
		int high = val + 1;
		int mid = low + (high - low) / 2;
		int ans = val;
		while(low <= high) {
			//System.out.println("loop");
			if(val / mid > l) {
				if(val / mid < ans) {
					ans = val / mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int prev = -1;
			int count = 0;
			StringBuilder temp = new StringBuilder();
			while(prev != n) {
				count ++;
				//System.out.println(prev);
				int next = search(prev, n);
				prev = next;
				temp.append(next).append(" ");
			}
			
			fout.append(count).append("\n").append(temp).append("\n");
		}
		System.out.print(fout);
	}
}
