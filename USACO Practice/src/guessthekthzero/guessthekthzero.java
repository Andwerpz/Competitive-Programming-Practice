//package guessthekthzero;

import java.util.*;
import java.io.*;

public class guessthekthzero {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int t = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(fin.readLine());
		int low = 1;
		int high = n;
		int oldLow = 1;
		int mid = low + (high - low) / 2;
		while(low < high - 1) {
			System.out.println("? " + low + " " + high);
			System.out.flush();
			int next = Integer.parseInt(fin.readLine());
			int numZeroes = (high - low + 1) - next;
			if(numZeroes >= 1) {
				oldLow = low;
				low = mid;
			}
			else {
				low = oldLow;
				high = mid;
			}
			mid = low + (high - low) / 2;
		} 
		System.out.println("? " + low + " " + low);
		System.out.flush();
		if(Integer.parseInt(fin.readLine()) == 1) {
			System.out.println("! " + low);
		}
		else {
			System.out.println("! " + high);
		}
	}
}
