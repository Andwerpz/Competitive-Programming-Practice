package diamond;

import java.util.*;
import java.io.*;

public class diamondver3 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("diamond.in"));
	    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("diamond.out")));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] d = new int[n];
		int[] pfx = new int[n];
		int[] sfx = new int[n];
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(fin.readLine());
			d[i] = next;
		}
		Arrays.sort(d);
		int last = 0;
		int max = 0;
		for(int i = 0; i < n; i++) {
			while(d[i] - d[last] > k) {
				last++;
			}
			if(i - last + 1 > max) {
				max = i - last + 1;
			}
			pfx[i] = max;
		}
		//System.out.println(max);
		last = n - 1;
		max = 0;
		for(int i = n - 1; i >= 0; i--) {
			while(d[last] - d[i] > k) {
				last--;
			}
			if(last - i + 1 > max) {
				max = last - i + 1;
			}
			sfx[i] = max;
		}
		int ans = 0;
		for(int i = 0; i < n - 1; i++) {
			if(pfx[i] + sfx[i + 1] > ans) {
				ans = pfx[i] + sfx[i + 1];
			}
		}
		fout.println(ans);
	}
}
