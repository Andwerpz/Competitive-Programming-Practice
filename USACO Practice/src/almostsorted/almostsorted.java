//package almostsorted;

import java.util.*;
import java.io.*;

public class almostsorted {
	public static void main(String[] args) throws IOException {
		
		//1508B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long k = Long.parseLong(st.nextToken()) - 1;
			int[] p = new int[n];
			for(int i = 1; i <= n; i++) {
				p[i - 1] = i;
			}
			long sum = 1;
			long prev = 0;
			long total = 0;
			int pointer = n - 1;
			boolean isValid = true;
			while(total != k) {
				//System.out.print(sum + prev + " ");
				while(total + sum + prev <= k) {
					//System.out.print(sum + prev + " ");
					long temp = sum;
					sum += prev;
					prev = temp;
					total += sum;
					pointer --;
				}
				//System.out.println();
				if(pointer < 0) {
					isValid = false;
					break;
				}
				else if(total == k) {
					int counter = n;
					for(int i = pointer; i < n; i++) {
						p[i] = counter;
						counter --;
					}
				}
				else {
					total ++;
					pointer --;
					if(pointer == -1) {
						isValid = false;
						break;
					}
					int temp = p[pointer];
					p[pointer] = p[pointer + 1];
					p[pointer + 1] = temp;
				}
				
				sum = 1;
				prev = 0;
				pointer = n - 1;
			}
			if(isValid) {
				for(int i = 0; i < n; i++) {
					fout.append(p[i] + " ");
				}
				fout.append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
