//package apartments;

import java.util.*;
import java.io.*;

public class apartments {
	
	static StreamTokenizer fin;
	static int nextInt() throws IOException {
		fin.nextToken();
		return (int)fin.nval;
	}
	
	static String nextString() throws IOException {
		fin.nextToken();
		return fin.sval;
	}
	
	public static void main(String[] args) throws IOException {
		
		//for each apartment, we assign the lowest request to it
		
		//hmm doesn't work, idk why
		//the tests run fine on my side
		
		fin = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		int n = nextInt();
		int m = nextInt();
		int k = nextInt();
		int[] p = new int[n];
		int[] a = new int[m];
		for(int i = 0; i < n; i++) {
			p[i] = nextInt();
		}
		for(int i = 0; i < m; i++) {
			a[i] = nextInt();
		}
		Arrays.parallelSort(a);
		Arrays.parallelSort(p);
		int pointer = 0;
		int ans = 0;
		for(int i = 0; i < m; i++) {
			int low = a[i] - k;
			int high = a[i] + k;
			while(pointer < n && p[pointer] < low) {
				pointer ++;
			}
			if(pointer == n) {
				break;
			}
			if(p[pointer] >= low && p[pointer] <= high) {
				pointer++;
				ans ++;
			}
		}
		System.out.println(ans);
	}
}
